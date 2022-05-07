#include <Utils.hpp>
#include <string>

int main(int argc, char* argv[]) {
  Log the_log(0);
  UsedMemory used_memory(the_log);

  Data* data = new Data();
  if(!ParseArgs(data, argc, argv)) {
    delete data;
    return -1;
  }
  PageContainer page(the_log, &used_memory);
  std::ifstream in(data->inp_path);
  if(!in)
  {
    std::cout << "File doesn't exist";
    return -1;
  }

  page.Load(in, data->threshold);

  the_log.Write(std::to_string(used_memory.used()));

  for (size_t i = 0; i < 5; ++i) {
    const auto& item = page.ByIndex(i);
    std::cout << item.name << ": " << item.score << std::endl;
    const auto& item2 = page.ById(std::to_string(i));
    std::cout << item2.name << ": " << item2.score << std::endl;
  }
  page.Reload(data->threshold);
  the_log.Write(std::to_string(used_memory.used()));
  delete data;
  return 0;
}