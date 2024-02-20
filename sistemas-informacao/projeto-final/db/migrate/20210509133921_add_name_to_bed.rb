class AddNameToBed < ActiveRecord::Migration[6.1]
  def change
    add_column :beds, :name, :string
  end
end
