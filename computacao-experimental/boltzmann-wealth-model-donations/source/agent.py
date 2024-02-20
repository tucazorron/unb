import mesa
from random import random

class MoneyAgent(mesa.Agent):
    def __init__(self, unique_id, model):
        super().__init__(unique_id, model)
        self.wealth = 1
        self.donation_probability = model.donation_probability

    def move(self):
        possible_steps = self.model.grid.get_neighborhood(
            self.pos, moore=True, include_center=False
        )
        new_position = self.random.choice(possible_steps)
        self.model.grid.move_agent(self, new_position)

    def give_money(self):
        cellmates = self.model.grid.get_cell_list_contents([self.pos])
        if len(cellmates) > 1:
            other = self.random.choice(cellmates)
            if self.wealth > other.wealth + 3 and self.donation_probability > random():
                donation = (self.wealth - other.wealth) // 2
                self.wealth -= donation
                other.wealth += donation
            else:
                self.wealth -= 1
                other.wealth += 1

    def step(self):
        self.move()
        if self.wealth > 0:
            self.give_money()
