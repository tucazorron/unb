class PatientsController < ApplicationController
  before_action :set_patient, only: [:show, :update, :destroy]

  def index
    @patients = Patient.all
  end

  def create
    @patient = Patient.new(patient_params)

    if @patient.save
     # Mark bed as *busy*
      @bed = Bed.find(patient_params["bed_id"])
      @bed['busy'] = true
      @bed.save
      redirect_to :authenticated_root
    else
      render json: @patient.errors, status: :unprocessable_entity
    end
  end

  def destroy
    @patient.destroy
  end

  def show
    @patient = Patient.find(params[:id])
  end

  def update
    if @patient.update(patient_params)
      redirect_to patients_path
    else
      render status: :unprocessable_entity
    end
  end

  private

  def set_patient
    @patient = Patient.find(params[:id])
  end

  def patient_params
    params.require(:patient).permit(:name, :rg, :age, :cause, :description, :gender_id, :bed_id)
  end

end
