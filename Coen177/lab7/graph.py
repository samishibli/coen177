import matplotlib.pyplot as plt

# Data
cache_sizes = [10, 50, 100, 250, 500]
fifo_faults = [9916, 9515, 9018, 7534, 5130]
lru_faults = [9915, 9510, 9029, 7532, 5207]
second_chance_faults = [9915, 9510, 9022, 7526, 5178]

# Plot
plt.plot(cache_sizes, fifo_faults, label='FIFO', marker='o')
plt.plot(cache_sizes, lru_faults, label='LRU', marker='o')
plt.plot(cache_sizes, second_chance_faults, label='Second Chance', marker='o')

# Labels and Title
plt.xlabel('Cache Size')
plt.ylabel('Page Faults')
plt.title('Page Fault Comparison of FIFO, LRU, and Second Chance Algorithms')
plt.legend()

# Show plot
plt.grid(True)
plt.show()
