import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime

# === Путь к архиву ===
CSV_PATH = "/home/maksys2011/home-scada/archive/archive.csv"

# === Читаем CSV ===
df = pd.read_csv(
    CSV_PATH,
    sep=";",
    names=["timestamp", "id", "name", "value", "state"]
)

# === Преобразуем время ===
df["time"] = df["timestamp"].apply(
    lambda t: datetime.fromtimestamp(t)
)

# === Сортируем по времени (ВАЖНО) ===
df = df.sort_values("time")

# === Строим график ===
plt.figure(figsize=(14, 6))

plt.plot(
    df["time"],
    df["value"],
    marker="o"
)

# === Подписи к точкам ===
for _, row in df.iterrows():
    label = f"{row['value']:.2f}\n{row['state']}"
    plt.annotate(
        label,
        (row["time"], row["value"]),
        textcoords="offset points",
        xytext=(0, 8),
        ha="center",
        fontsize=8
    )

# === Оформление ===
plt.title("Temperature Sensor")
plt.xlabel("Time")
plt.ylabel("Value")
plt.grid(True)
plt.tight_layout()

# === Показ ===
plt.show()


