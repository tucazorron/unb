class HomeController < ApplicationController
  def index
    @beds = Bed.all
  end
end
