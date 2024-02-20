# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the bin/rails db:seed command (or create!d alongside the database with db:setup).
#
# Examples:
#
#   movies = Movie.create!([{ name: 'Star Wars' }, { name: 'Lord of the Rings' }])
#   Character.create(name: 'Luke', movie: movies.first)

User.create([
  {email: 'test@gmail.com', password: '123456'},
  {email: 'example@gmail.com', password: '123456'}
])

Gender.create!([{ name: 'Masculino' }, {name: 'Feminino'}])

BedType.create!([
  { type_name: 'Leito de Internação' },
  { type_name: 'Leito de Observação' },
  { type_name: 'Leito de Isolamento' },
  { type_name: 'Leito de Isolamento Reverso' },
  { type_name: 'Leito Planejado' },
  { type_name: 'Leito de Tratamento Intensivo' },
])

Wing.create!([{name: 'Ala Norte'}, { name: 'Ala Sul' }, { name: 'Ala Leste' }, { name: 'Ala Oeste' } ])

Bed.create!([
  {busy: true, bed_type_id: 1, wing_id: 1},
  {busy: false, bed_type_id: 2, wing_id: 2},
  {busy: true, bed_type_id: 3, wing_id: 3},
  {busy: true, bed_type_id: 4, wing_id: 4},
  {busy: false, bed_type_id: 4, wing_id: 1},
  {busy: false, bed_type_id: 4, wing_id: 1},
])

Patient.create!([
  {name: 'Artur', rg: '123456789', age: 82, cause: 'COVID-19', description: 'Está em tratamento de COVID-19', gender_id: 1, bed_id: 1},
  {name: 'Vinicius', rg: '987654321', age: 66, cause: 'COVID-19', description: 'Está em tratamento de COVID-19', gender_id: 1, bed_id: 2},
  {name: 'Ana', rg: '987654321', age: 54, cause: 'COVID-19', description: 'Está em tratamento de COVID-19', gender_id: 2, bed_id: 3},
  {name: 'Paula', rg: '987654321', age: 58, cause: 'COVID-19', description: 'Está em tratamento de COVID-19', gender_id: 2, bed_id: 4},
])

