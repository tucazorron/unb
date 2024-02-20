class Patient < ApplicationRecord
  belongs_to :bed, optional: true
  belongs_to :gender
end
