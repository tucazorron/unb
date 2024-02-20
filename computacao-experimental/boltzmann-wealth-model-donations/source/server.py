import mesa
from .model import BoltzmannWealthModel


def agent_portrayal(agent):
    portrayal = {
        "Shape": "circle",
        "Filled": "true",
        "r": 0.5
    }

    if agent.wealth > 0:
        portrayal["Color"] = "red"
        portrayal["Layer"] = 0
    else:
        portrayal["Color"] = "grey"
        portrayal["Layer"] = 1
        portrayal["r"] = 0.2
    return portrayal


grid = mesa.visualization.CanvasGrid(agent_portrayal, 10, 10, 500, 500)

chart = mesa.visualization.ChartModule(
    [{
        "Label": "Gini",
        "Color": "#0000FF"
    }],
    data_collector_name="datacollector"
)

wealth_standard_deviation = mesa.visualization.ChartModule(
    [{
        "Label": "Wealth Standard Deviation",
        "Color": "#007700"
    }],
    data_collector_name="datacollector"
)

model_params = {
    "N": mesa.visualization.Slider(
        "Number of agents",
        100,
        2,
        200,
        1,
        description="Choose how many agents to include in the model",
    ),
    "D": mesa.visualization.Slider(
        "Donation probability",
        0,
        0,
        1,
        0.1,
        description="Choose the probability that an agent will donate money",
    ),
    "width": 10,
    "height": 10,
}

server = mesa.visualization.ModularServer(
    BoltzmannWealthModel, [grid, chart, wealth_standard_deviation], "Money Model", model_params
)

server.port = 8521
