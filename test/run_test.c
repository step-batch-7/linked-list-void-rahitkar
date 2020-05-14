#include "test_add.h"
#include "test_remove.h"
#include "lindedlist_test.h"

int main(void)
{
  describe("create_list");
  it("Should create a list with null in first and last and with length zero", assert_empty_list());

  test_add_functions();
}