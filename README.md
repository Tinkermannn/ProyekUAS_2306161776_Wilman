# Simulasi Peluruhan Radioaktif Radon-222 Menggunakan Metode Euler

**Nama:** Wilman Saragih Sitio  
**NPM:** 2306161776  
**Mata Kuliah/Kelas:** Komputasi Numerik/02

## Deskripsi Program

Sedara garis besarnya, pada studi kasus ini mengimplementasikan metode Euler untuk memodelkan peluruhan radioaktif isotop Radon-222 (²²²Rn). Simulasi ini bertujuan untuk membandingkan hasil numerik dengan solusi analitik eksak dan menganalisis pengaruh ukuran langkah waktu (Δt) terhadap akurasi perhitungan.

### Model Matematika

Peluruhan radioaktif mengikuti hukum peluruhan eksponensial yang dinyatakan dalam persamaan diferensial orde pertama:

$$\frac{dN(t)}{dt} = -\lambda N(t)$$

di mana:
- $N(t)$ = jumlah atom radioaktif pada waktu $t$
- $\lambda$ = konstanta peluruhan

**Solusi Analitik:**
$$N(t) = N_0 e^{-\lambda t}$$

**Implementasi Metode Euler:**
$$N_{i+1} = N_i + \Delta t \cdot (-\lambda N_i) = N_i(1 - \lambda \Delta t)$$

### Parameter Radon-222

- **Waktu paruh:** $T_{1/2} = 3.8235$ hari = $330350.4$ detik
- **Konstanta peluruhan:** $\lambda = \frac{\ln(2)}{T_{1/2}} \approx 2.098 \times 10^{-6}$ s⁻¹
- **Jumlah atom awal:** $N_0 = 1.0 \times 10^{15}$ atom
- **Periode simulasi:** 4 kali waktu paruh (≈15.3 hari)

### Variasi Time Step

Program menguji 5 variasi ukuran langkah waktu:
- $\Delta t_1 = \frac{T_{1/2}}{10} = 33035.04$ s
- $\Delta t_2 = \frac{T_{1/2}}{20} = 16517.52$ s  
- $\Delta t_3 = \frac{T_{1/2}}{50} = 6607.01$ s
- $\Delta t_4 = \frac{T_{1/2}}{100} = 3303.50$ s
- $\Delta t_5 = \frac{T_{1/2}}{200} = 1651.75$ s

### Evaluasi Akurasi

**Error Absolut:**
$$E_{abs} = |N_{numerik} - N_{eksak}|$$

**Error Relatif:**
$$E_{rel} = \left(\frac{E_{abs}}{N_{eksak}}\right) \times 100\%$$

## Cara Menjalankan Program

### Kompilasi dan Eksekusi (C)

1. **Kompilasi program:**
   ```bash
   cd code
   gcc -o main main.c -lm
   ```
   
2. **Jalankan program:**
   ```bash
   ./main
   ```
### Kompilasi dan Eksekusi Python
1. **Install library yang diperlukan program:**
   ```bash
   pip install matplotlib numpy
   ```
2. **Jalankan program:**
   ```bash
   cd code
   python plot.py
   ```
### Persyaratan Sistem

- **Compiler C dan Interpreter Python**
- **Library math**
- **Sistem operasi:** Linux/macOS/Windows (dengan MinGW)
## Hasil Utama

1. **Konvergensi:** Error menurun secara konsisten dengan pengecilan Δt sesuai teori metode Euler O(Δt)
2. **Stabilitas:** Semua simulasi stabil untuk rentang parameter yang digunakan
3. **Akurasi:** Metode memberikan hasil yang dapat diterima dengan error relatif < 1% untuk Δt terkecil
4. **Validasi:** Hasil numerik menunjukkan pola peluruhan eksponensial yang konsisten dengan teori


