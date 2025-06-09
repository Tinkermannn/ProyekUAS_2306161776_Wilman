/**
 * ========================================================================
 * PROGRAM SIMULASI PELURUHAN RADIOAKTIF RADON-222 MENGGUNAKAN METODE EULER
 * ========================================================================
 * 
 * Program ini mensimulasikan peluruhan radioaktif isotop Radon-222 menggunakan
 * metode numerik Euler untuk menyelesaikan persamaan diferensial:
 * 
 * dN/dt = -λN
 * 
 * di mana:
 * - N(t) = jumlah atom pada waktu t
 * - λ = konstanta peluruhan radioaktif
 * - Solusi analitik: N(t) = N₀ * e^(-λt)
 * 
 * Nama: Wilman Saragih Sitio
 * NPM : 2306161776
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * STRUKTUR DATA UNTUK MENYIMPAN HASIL SIMULASI
 * ============================================
 * 
 * Struktur ini menyimpan data hasil simulasi untuk setiap step waktu,
 * termasuk perbandingan antara hasil numerik dan analitik serta analisis error.
 */
typedef struct {
    double time_s;                    // Waktu dalam detik
    double N_numerical;               // Jumlah atom hasil metode Euler
    double N_analytical;              // Jumlah atom hasil solusi analitik
    double error_absolute;            // Error absolut = |N_numerik - N_analitik|
    double error_relative_percent;    // Error relatif dalam persen
} SimulationStep;

/**
 * FUNGSI UTAMA UNTUK SIMULASI PELURUHAN RADIOAKTIF MENGGUNAKAN METODE EULER
 * ========================================================================
 * 
 * Metode Euler adalah metode numerik untuk menyelesaikan persamaan diferensial
 * orde pertama dengan pendekatan:
 * 
 * N(t+Δt) = N(t) + Δt * dN/dt
 * N(t+Δt) = N(t) + Δt * (-λN(t))
 * N(t+Δt) = N(t) * (1 - λΔt)
 * 
 * Parameter:
 * @param N0                  - Jumlah atom awal
 * @param lambda              - Konstanta peluruhan (s⁻¹)
 * @param t_initial           - Waktu awal simulasi (s)
 * @param t_final             - Waktu akhir simulasi (s)
 * @param delta_t             - Ukuran step waktu (s)
 * @param results_array_ptr   - Pointer ke array hasil simulasi
 * 
 * Return:
 * @return int - Jumlah step simulasi yang berhasil dilakukan
 */
int euler_radioactive_decay(
    double N0, double lambda,
    double t_initial, double t_final, double delta_t,
    SimulationStep** results_array_ptr
) {
    // VALIDASI INPUT
    // ==============
    // Memastikan delta_t positif untuk menghindari error numerik
    if (delta_t <= 0) {
        printf("Error: delta_t harus positif.\n");
        *results_array_ptr = NULL;
        return 0;
    }

    // ALOKASI MEMORI DINAMIS
    // ======================
    // Estimasi jumlah step yang dibutuhkan dan alokasi memori
    int estimated_steps = (int)((t_final - t_initial) / delta_t) + 2;
    *results_array_ptr = (SimulationStep*)malloc(estimated_steps * sizeof(SimulationStep));
    
    // Validasi alokasi memori
    if (*results_array_ptr == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk hasil simulasi.\n");
        return 0;
    }

    // INISIALISASI VARIABEL SIMULASI
    // ==============================
    double current_N = N0;        // Jumlah atom saat ini (dimulai dari N₀)
    double current_t = t_initial; // Waktu saat ini
    int step_count = 0;           // Counter step simulasi

    // HEADER TABEL OUTPUT
    // ===================
    printf("\nSimulasi Peluruhan Radon-222 dengan delta_t = %.4f s (%.2f jam):\n", 
           delta_t, delta_t/3600.0);
    printf("--------------------------------------------------------------------------------------\n");
    printf("| Waktu (s) | N Numerik      | N Analitik     | Error Absolut  | Error Relatif (%%) |\n");
    printf("|-----------|----------------|----------------|----------------|-------------------|\n");

    // LOOP UTAMA SIMULASI METODE EULER
    // =================================
    while (current_t <= t_final + delta_t / 2.0) {
        
        // REALLOKASI MEMORI (IF NEEDED)
        // =================================
        // Jika step melebihi estimasi, gandakan ukuran array
        if (step_count >= estimated_steps) {
            estimated_steps *= 2;
            SimulationStep* temp = (SimulationStep*)realloc(*results_array_ptr, 
                                                           estimated_steps * sizeof(SimulationStep));
            if (temp == NULL) {
                printf("Error: Gagal realloc memori.\n");
                return step_count;
            }
            *results_array_ptr = temp;
        }

        // PERHITUNGAN SOLUSI ANALITIK
        // ===========================
        // Solusi eksak: N(t) = N₀ * e^(-λt)
        double N_exact = N0 * exp(-lambda * current_t);
        
        // ANALISIS ERROR
        // ==============
        // Error absolut: |N_numerik - N_analitik|
        double abs_error = fabs(current_N - N_exact);
        
        // Error relatif dalam persen: (|error| / N_analitik) * 100%
        // Validasi pembagian dengan nol untuk stabilitas numerik
        double rel_error_pct = (N_exact != 0 && N_exact != 0.0) ? 
                              (abs_error / N_exact) * 100.0 : 0.0;

        // PENYIMPANAN HASIL step SAAT INI
        // ==================================
        (*results_array_ptr)[step_count].time_s = current_t;
        (*results_array_ptr)[step_count].N_numerical = current_N;
        (*results_array_ptr)[step_count].N_analytical = N_exact;
        (*results_array_ptr)[step_count].error_absolute = abs_error;
        (*results_array_ptr)[step_count].error_relative_percent = rel_error_pct;

        // OUTPUT HASIL KE KONSOL (SAMPLING)
        // =================================
        // Menampilkan 10% step untuk menghindari output terlalu panjang
        int print_interval = estimated_steps / 10;
        if (print_interval < 1) print_interval = 1;

        if (step_count % print_interval == 0 || current_t >= t_final - delta_t / 2.0) {
            printf("| %9.2f | %14.3e | %14.3e | %14.3e | %17.4f |\n",
                   current_t, current_N, N_exact, abs_error, rel_error_pct);
        }

        // KONDISI TERMINASI
        // =================
        // Stop iterasi jika sudah mencapai waktu akhir
        if (current_t >= t_final - delta_t / 2.0 && step_count > 0) break;

        // IMPLEMENTASI METODE EULER
        // =========================
        // Hitung turunan: dN/dt = -λN
        double dN_dt = -lambda * current_N;
        
        // Update nilai N menggunakan formula Euler: N_baru = N_lama + Δt * (dN/dt)
        current_N = current_N + delta_t * dN_dt;
        
        // Advance waktu: t_baru = t_lama + Δt
        current_t = current_t + delta_t;
        
        // Increment counter step
        step_count++;
    }
    
    printf("--------------------------------------------------------------------------------------\n");
    return step_count;
}

/**
 * FUNGSI UTAMA PROGRAM
 * ====================
 * 
 * Fungsi main menjalankan simulasi peluruhan Radon-222 dengan berbagai
 * ukuran step waktu (delta_t) untuk menganalisis akurasi metode Euler.
 */
int main() {
    // PARAMETER FISIK RADON-222
    // =========================
    double N0_initial = 1.0e15;           // Jumlah atom awal (10^15 atom)
    double T_half_days = 3.8235;           // Waktu paruh Radon-222 dalam hari
    double T_half_seconds = T_half_days * 24.0 * 60.0 * 60.0; // Konversi ke detik
    
    // PERHITUNGAN KONSTANTA PELURUHAN
    // ===============================
    // λ = ln(2) / T_half (hubungan fundamental radioaktivitas)
    double lambda_decay = log(2.0) / T_half_seconds;

    // PARAMETER SIMULASI
    // ==================
    double t_start = 0.0;                  // Waktu awal (detik)
    double t_end = 4.0 * T_half_seconds;   // Waktu akhir = 4 × waktu paruh

    // ARRAY UKURAN step WAKTU UNTUK ANALISIS KONVERGENSI
    // =====================================================
    // Berbagai delta_t sebagai fraksi dari waktu paruh untuk studi konvergensi
    double delta_t_values[] = {
        T_half_seconds / 10.0,   // T_half/10  ≈ 9.18 jam
        T_half_seconds / 20.0,   // T_half/20  ≈ 4.59 jam  
        T_half_seconds / 50.0,   // T_half/50  ≈ 1.84 jam
        T_half_seconds / 100.0,  // T_half/100 ≈ 0.92 jam
        T_half_seconds / 200.0   // T_half/200 ≈ 0.46 jam
    };
    int num_delta_t_cases = sizeof(delta_t_values) / sizeof(delta_t_values[0]);

    // HEADER INFORMASI PROGRAM
    // ========================
    printf("Simulasi Peluruhan Radioaktif RADON-222 Menggunakan Metode Euler\n");
    printf("N0 = %.2e atom\n", N0_initial);
    printf("Waktu Paruh (T_half) = %.2f hari (%.2f s)\n", T_half_days, T_half_seconds);
    printf("Konstanta Peluruhan (lambda) = %.4e s^-1\n", lambda_decay);
    printf("Simulasi dari t = %.1f s hingga t = %.1f s (sekitar %.1f hari)\n", 
           t_start, t_end, t_end / (24.0 * 3600.0));
    printf("======================================================================\n");

    // LOOP UTAMA: SIMULASI UNTUK BERBAGAI DELTA_T
    // ===========================================
    for (int i = 0; i < num_delta_t_cases; i++) {
        double current_delta_t = delta_t_values[i];
        SimulationStep* simulation_results = NULL;

        // PANGGIL FUNGSI SIMULASI EULER
        // =============================
        int actual_steps = euler_radioactive_decay(
            N0_initial, lambda_decay,
            t_start, t_end, current_delta_t,
            &simulation_results
        );

        // VALIDASI HASIL SIMULASI
        // =======================
        if (simulation_results != NULL && actual_steps > 0) {
            
            // TAMPILKAN STATISTIK SIMULASI
            // ============================
            printf("Total step untuk delta_t = %.2f s (%.2f jam) adalah %d.\n",
                   current_delta_t, current_delta_t / 3600.0, actual_steps);
            printf("Error absolut akhir (pada t=%.1f s): %.3e atom\n",
                   simulation_results[actual_steps - 1].time_s,
                   simulation_results[actual_steps - 1].error_absolute);
            printf("Error relatif akhir: %.4f %%\n",
                   simulation_results[actual_steps - 1].error_relative_percent);

            // EKSPOR DATA KE FILE CSV
            // =======================
            // Buat nama file unik berdasarkan delta_t
            char filename[100];
            sprintf(filename, "output_%.0f.csv", current_delta_t);
            FILE *fp = fopen(filename, "w");

            if (fp != NULL) {
                // Header CSV
                fprintf(fp, "Time_s,N_Numerical,N_Analytical,Error_Absolute,Error_Relative_Percent\n");
                
                // Tulis semua data simulasi ke CSV
                for (int j = 0; j < actual_steps; j++) {
                    fprintf(fp, "%.4f,%.6e,%.6e,%.6e,%.6f\n",
                            simulation_results[j].time_s,
                            simulation_results[j].N_numerical,
                            simulation_results[j].N_analytical,
                            simulation_results[j].error_absolute,
                            simulation_results[j].error_relative_percent);
                }
                fclose(fp);
                printf("Data hasil simulasi disimpan ke: %s\n", filename);
            } else {
                printf("Error: Gagal membuka file %s untuk ditulis.\n", filename);
            }

            printf("======================================================================\n");

            // Dealokasi memori untuk mencegah memory leak
            free(simulation_results);
            simulation_results = NULL;
            
        } else {
            // ERROR HANDLING
            printf("Simulasi gagal atau tidak ada step untuk delta_t = %.2f s.\n", current_delta_t);
            printf("======================================================================\n");
        }
    }

    return 0; 
}
