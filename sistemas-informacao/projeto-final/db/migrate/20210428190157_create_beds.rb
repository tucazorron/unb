class CreateBeds < ActiveRecord::Migration[6.1]
  def change
    create_table :beds do |t|
      t.boolean :busy

      t.timestamps
    end
  end
end
