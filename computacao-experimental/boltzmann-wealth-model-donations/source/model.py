import mesa
import statistics
from .agent import MoneyAgent


def compute_gini(model):
    agent_wealths = [agent.wealth for agent in model.schedule.agents]
    x = sorted(agent_wealths)
    N = model.num_agents
    B = sum(xi * (N - i) for i, xi in enumerate(x)) / (N * sum(x))
    return 1 + (1 / N) - 2 * B

def compute_wealth_standard_deviation(model):
    return statistics.stdev([agent.wealth for agent in model.schedule.agents])

class BoltzmannWealthModel(mesa.Model):
    def __init__(self, N=100, width=10, height=10, D=0):
        self.num_agents = N
        self.donation_probability = D
        self.grid = mesa.space.MultiGrid(width, height, True)
        self.donation_probability = D
        self.schedule = mesa.time.RandomActivation(self)
        self.datacollector = mesa.DataCollector(
            model_reporters={
                "gini": compute_gini,
                "wealth_standard_deviation": compute_wealth_standard_deviation
            },
        )
        
        for i in range(self.num_agents):
            a = MoneyAgent(i, self)
            self.schedule.add(a)
            x = self.random.randrange(self.grid.width)
            y = self.random.randrange(self.grid.height)
            self.grid.place_agent(a, (x, y))

        self.running = True
        self.datacollector.collect(self)

    def step(self):
        self.schedule.step()
        self.datacollector.collect(self)

    def run_model(self, n=200):
        for i in range(n):
            self.step()
