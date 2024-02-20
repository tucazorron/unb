class AddWingToBed < ActiveRecord::Migration[6.1]
  def change
    add_reference :beds, :wing, null: false, foreign_key: true
  end
end
