class RemovePatientFromBed < ActiveRecord::Migration[6.1]
  def change
    remove_column :beds, :patient_id, :integer
  end
end
