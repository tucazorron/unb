class AddBedTypeToBed < ActiveRecord::Migration[6.1]
  def change
    add_reference :beds, :bed_type, null: false, foreign_key: true
  end
end
