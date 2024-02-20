class BedsController < ApplicationController
  before_action :set_bed, only: [:show, :update, :destroy]

  def index
    @beds = Bed.all
  end

  def create
    @bed = Bed.new(bed_params)
    if @bed.save
      redirect_to :authenticated_root
    else
      render json: @bed.errors, status: :unprocessable_entity
    end
  end

  def destroy
    @bed.destroy
  end

  def show
    @bed = Bed.find(params[:id])
  end

  def update
    if @bed.update(bed_params)
      redirect_to beds_path
    else
      render status: :unprocessable_entity
    end
  end

  private

  def set_bed
    @bed = Bed.find(params[:id])
  end

  def bed_params
    params.require(:bed).permit(:busy, :bed_type_id, :wing_id)
  end

end
