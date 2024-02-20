import mesa
import numpy as np
import pandas as pd
from datetime import datetime
from source.model import BoltzmannWealthModel

steps = 200
iterations = 200

params = {
    "N": 100,
    "D": np.arange(0, 1.1, 0.5),
    "width": 10,
    "height": 10,
}


if __name__ == "__main__":
    data = mesa.batch_run(
        BoltzmannWealthModel,
        params,
        iterations,
        steps,
    )

    dataframe = pd.DataFrame(data)

    dataframe.to_csv("dataset.csv")
