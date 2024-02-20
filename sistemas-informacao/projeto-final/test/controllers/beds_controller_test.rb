require "test_helper"

class BedsControllerTest < ActionDispatch::IntegrationTest
  test "should get index" do
    get beds_index_url
    assert_response :success
  end

  test "should get new" do
    get beds_new_url
    assert_response :success
  end

  test "should get create" do
    get beds_create_url
    assert_response :success
  end

  test "should get destroy" do
    get beds_destroy_url
    assert_response :success
  end
end
