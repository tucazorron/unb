class AddGenderToPatient < ActiveRecord::Migration[6.1]
  def change
    add_reference :patients, :gender, null: false, foreign_key: true
  end
end
