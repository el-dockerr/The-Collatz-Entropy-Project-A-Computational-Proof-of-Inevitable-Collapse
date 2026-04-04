import matplotlib.pyplot as plt
import numpy as np
import math

# --- KONFIGURATION ---
START_NUMBERS = [
    27,         # Der Klassiker (wächst stark)
    670617279,  # Ein lokales Maximum
    97,         # Kleines "Monster"
    (2**50)-1   # Mersenne Zahl (Startet hoch, fällt tief)
]

def collatz_trajectory(n):
    """Berechnet die Trajektorie und gibt Bits (log2) zurück"""
    values = [n]
    bits = [math.log2(n)]
    
    curr = n
    while curr > 1:
        if curr % 2 == 0:
            curr = curr // 2
        else:
            curr = 3 * curr + 1
        values.append(curr)
        bits.append(math.log2(curr))
    return bits

def plot_gravity_well():
    plt.figure(figsize=(14, 8))
    plt.style.use('dark_background') # Hacker-Style für YouTube
    
    max_steps = 0
    max_height = 0
    
    colors = ['cyan', 'lime', 'magenta', 'yellow']
    
    print("Simuliere Trajektorien...")
    
    # 1. Die echten Zahlen plotten
    for idx, n in enumerate(START_NUMBERS):
        y_data = collatz_trajectory(n)
        x_data = range(len(y_data))
        
        # Stats für die Skalierung
        max_steps = max(max_steps, len(y_data))
        max_height = max(max_height, max(y_data))
        
        plt.plot(x_data, y_data, 
                 label=f'n={n}', 
                 color=colors[idx % len(colors)], 
                 linewidth=1.5, 
                 alpha=0.8)

    # 2. Die "Todeslinie" (Gravity Line) berechnen
    # Wir starten am höchsten Punkt des Graphs und ziehen die Linie nach unten
    # Steigung: -0.138 Bits pro Schritt (aus Paper 2)
    gravity_slope = -0.138 
    
    # Wir setzen den Startpunkt der Linie etwas über das Maximum, damit man es gut sieht
    start_y = max_height
    gravity_line_x = np.array([0, max_steps])
    gravity_line_y = start_y + (gravity_line_x * gravity_slope)
    
    plt.plot(gravity_line_x, gravity_line_y, 
             color='red', 
             linestyle='--', 
             linewidth=3, 
             label='The Death Line (-0.415 bits drift)')

    # --- STYLE & LABELS ---
    plt.title('THE DIGITAL GRAVITY WELL (Paper 3 Visualization)', fontsize=20, color='white', pad=20)
    plt.xlabel('Steps (Iterations)', fontsize=14)
    plt.ylabel('Information Content (Bits / log2)', fontsize=14)
    plt.grid(True, which='both', linestyle='--', alpha=0.3)
    plt.legend(fontsize=12)
    
    # Annotation
    plt.text(max_steps/2, max_height + 5, 
             'ENTROPY DECAY ZONE', 
             color='red', fontsize=16, ha='center', weight='bold')

    plt.tight_layout()
    
    # Speichern und Anzeigen
    filename = 'collatz_gravity_well.png'
    plt.savefig(filename, dpi=300)
    print(f"Grafik gespeichert als {filename}")
    plt.show()

if __name__ == "__main__":
    plot_gravity_well()