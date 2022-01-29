import pandas as pd

data = pd.read_csv("../data.csv", sep=';')
data["Time"] = pd.to_datetime(data['Time'], format='%M:%S.%f')
data.set_index("Time", inplace=True)

ax1 = data["dt update"].rolling(window=10).mean().plot(legend=True, label='Updating delay in seconds', figsize=(10, 5),
                                                       title="Initial number of Ants : " + str(data.columns[-1]))
ax2 = ax1.twinx()
ax1.legend(loc='upper left')
ax2.spines['right'].set_position(('axes', 1.0))

data["nb_markers"].plot(ax=ax2, color='red', legend=True, label="Number of markers").legend(loc='upper right')
ax2.grid(False)
ax1.grid(False)
fig = ax1.get_figure()
fig = ax2.get_figure()
fig.savefig('../data.png')
