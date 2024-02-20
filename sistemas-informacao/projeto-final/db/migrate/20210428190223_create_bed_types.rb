class CreateBedTypes < ActiveRecord::Migration[6.1]
  def change
    create_table :bed_types do |t|
      t.string :type_name

      t.timestamps
    end
  end
end
