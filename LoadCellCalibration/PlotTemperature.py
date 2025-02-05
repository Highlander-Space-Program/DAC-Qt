import matplotlib.pyplot as plt
from labjack import ljm
#Name: Luis Bojorquez
#Date: 10/29/2024
# Open the LabJack device
handle = ljm.openS("T7", "USB", "ANY")

# Set up the analog input channel
ljm.eWriteName(handle, "AIN0_NEGATIVE_CH", 1)
ljm.eWriteName(handle, "AIN0_EF_INDEX", 22)
ljm.eWriteName(handle, "AIN0_EF_CONFIG_A", 3)
ljm.eWriteName(handle, "AIN0_RANGE", 0.1)
ljm.eWriteName(handle, "AIN0_RESOLUTION_INDEX", 8)

# Initialize data storage for plotting
y = []  # List to hold temperature readings
x = []  # List to hold time (or count) values
count = 0  # Counter for the x-axis

# Create a plot
plt.ion()  # Turn on interactive mode
fig, ax = plt.subplots()
line, = ax.plot(x, y, 'r-')  # Line object for updating
ax.set_xlabel("Time (s)")
ax.set_ylabel("Temperature (C)")
ax.set_ylim(20, 25)  # Adjust according to expected temperature range
plt.title("Real-time Temperature Readings")

# Continuously read temperature and update the plot
try:
    while True:
        # Read temperature from the LabJack
        temperature = ljm.eReadName(handle, "AIN0_EF_READ_A")
        print("Temperature (C):", temperature)

        # Append the new temperature and time value
        y.append(temperature)
        count += 1
        x.append(count)

        # Update the plot
        line.set_xdata(x)
        line.set_ydata(y)
        ax.relim()  # Recalculate limits
        ax.autoscale_view()  # Autoscale view
        plt.pause(1)  # Pause for 1 second before next read

except KeyboardInterrupt:
    print("Stopped by user")

finally:
    # Close the LabJack handle and show the final plot
    ljm.close(handle)
    plt.ioff()  # Turn off interactive mode
    plt.show()  # Show the final plot
