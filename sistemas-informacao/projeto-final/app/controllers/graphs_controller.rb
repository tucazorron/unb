class GraphsController < ApplicationController

    def index
        @beds = Bed.all
        @data = Bed.group(:busy).count 
        datadata= 1
    end
    
    def create
    end

    def destroy
    end

    def show
    end

end
