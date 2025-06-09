"""
DOKUMENTASI PROGRAM PLOT HASIL SIMULASI PELURUHAN RADON-222
===============================================
"""

import matplotlib.pyplot as plt
import numpy as np

# ================== BAGIAN 1: INISIALISASI DATA ==================

# Data waktu simulasi (dalam detik)
# Waktu simulasi dari 0 hingga sekitar 15.3 hari dengan interval tetap
waktu = np.array([0.00, 132140.16, 264280.32, 396420.48, 528560.64,
                 660700.80, 792840.96, 924981.12, 1057121.28, 1189261.44, 1321401.60])

# Konversi waktu dari detik ke hari
# 1 hari = 24 jam × 3600 detik = 86400 detik
waktu_hari = waktu / (24 * 3600)

# ================== BAGIAN 2: DATA HASIL SIMULASI NUMERIK ==================

# Simulasi dengan dt = 33035 detik (≈ 9.18 jam) - time step besar
N_dt_33035 = np.array([1.000e+15, 7.503e+14, 5.629e+14, 4.223e+14, 3.168e+14,
                       2.377e+14, 1.783e+14, 1.338e+14, 1.004e+14, 7.532e+13, 5.651e+13])

# Simulasi dengan dt = 16518 detik (≈ 4.59 jam) - time step sedang
N_dt_16518 = np.array([1.000e+15, 7.541e+14, 5.687e+14, 4.289e+14, 3.235e+14,
                       2.439e+14, 1.840e+14, 1.387e+14, 1.046e+14, 7.890e+13, 5.950e+13])

# Simulasi dengan dt = 6607 detik (≈ 1.84 jam) - time step menengah
N_dt_6607 = np.array([1.000e+15, 7.564e+14, 5.721e+14, 4.327e+14, 3.273e+14,
                      2.476e+14, 1.873e+14, 1.417e+14, 1.071e+14, 8.104e+13, 6.130e+13])

# Simulasi dengan dt = 3304 detik (≈ 0.92 jam) - time step kecil
N_dt_3304 = np.array([1.000e+15, 7.571e+14, 5.732e+14, 4.340e+14, 3.286e+14,
                      2.488e+14, 1.884e+14, 1.426e+14, 1.080e+14, 8.176e+13, 6.190e+13])

# Simulasi dengan dt = 1652 detik (≈ 0.46 jam) - time step sangat kecil
N_dt_1652 = np.array([1.000e+15, 7.575e+14, 5.738e+14, 4.346e+14, 3.292e+14,
                      2.494e+14, 1.889e+14, 1.431e+14, 1.084e+14, 8.211e+13, 6.220e+13])

# ================== BAGIAN 3: SOLUSI ANALITIK ==================

# Parameter Radon-222
N0 = 1.00e+15  # Jumlah atom awal
lambda_decay = 2.0982e-06  # Konstanta peluruhan (s⁻¹)

# Perhitungan solusi analitik menggunakan hukum peluruhan eksponensial
# N(t) = N₀ × e^(-λt)
# Ini adalah solusi eksak untuk persamaan diferensial dN/dt = -λN
N_analitik = N0 * np.exp(-lambda_decay * waktu)

# ================== BAGIAN 4: VISUALISASI PERBANDINGAN ==================

# FIGURE 1: Grafik perbandingan hasil numerik vs analitik
plt.figure(figsize=(10, 6))

# Plot solusi analitik sebagai referensi
plt.plot(waktu_hari, N_analitik/1e14, 'k-', linewidth=2, label='Analitik')

# Plot hasil simulasi numerik dengan berbagai delta_t
plt.plot(waktu_hari, N_dt_33035/1e14, 'r--', label='dt = 9.18 jam')
plt.plot(waktu_hari, N_dt_16518/1e14, 'b--', label='dt = 4.59 jam')
plt.plot(waktu_hari, N_dt_6607/1e14, 'c--', label='dt = 1.84 jam')
plt.plot(waktu_hari, N_dt_3304/1e14, 'g--', label='dt = 0.92 jam')
plt.plot(waktu_hari, N_dt_1652/1e14, 'm--', label='dt = 0.46 jam')

# Konfigurasi grafik
plt.xlabel('Waktu (hari)')
plt.ylabel('Jumlah Atom (×10¹⁴)')
plt.title('Peluruhan Radon-222: Numerik vs Analitik')
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()

# ================== BAGIAN 5: ANALISIS ERROR ==================

# FIGURE 2: Grafik error relatif untuk menganalisis akurasi
plt.figure(figsize=(10, 6))

# Data error relatif (dalam persen) untuk setiap simulasi
# Error relatif = |N_numerik - N_analitik| / N_analitik × 100%
error_33035 = np.array([0.0000, 1.0027, 1.9953, 2.9780, 3.9508, 4.9139, 5.8673, 6.8112, 7.7456, 8.6706, 9.5864])
error_16518 = np.array([0.0000, 0.4906, 0.9789, 1.4647, 1.9482, 2.4293, 2.9080, 3.3844, 3.8584, 4.3301, 4.7995])
error_6607  = np.array([0.0000, 0.1938, 0.3872, 0.5802, 0.7729, 0.9652, 1.1571, 1.3487, 1.5398, 1.7306, 1.9211])
error_3304  = np.array([0.0000, 0.0965, 0.1929, 0.2892, 0.3854, 0.4815, 0.5775, 0.6735, 0.7693, 0.8651, 0.9607])
error_1652  = np.array([0.0000, 0.0481, 0.0963, 0.1444, 0.1924, 0.2405, 0.2885, 0.3365, 0.3845, 0.4325, 0.4804])

# Plot error relatif dengan marker berbeda untuk setiap simulasi
plt.plot(waktu_hari, error_33035, 'r-o', label='dt = 9.18 jam')
plt.plot(waktu_hari, error_16518, 'b-s', label='dt = 4.59 jam')
plt.plot(waktu_hari, error_6607,  'c-v', label='dt = 1.84 jam')
plt.plot(waktu_hari, error_3304,  'g-^', label='dt = 0.92 jam')
plt.plot(waktu_hari, error_1652,  'm-d', label='dt = 0.46 jam')

# Konfigurasi grafik error
plt.xlabel('Waktu (hari)')
plt.ylabel('Error Relatif (%)')
plt.title('Error Relatif vs Waktu')
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()

# Show kedua grafik
plt.show()