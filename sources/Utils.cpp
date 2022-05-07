// Copyright 2022 wm8

#include <Utils.hpp>

bool ParseArgs(Data* data, int argc, char **argv) {
  po::options_description desc("Options:");
  desc.add_options()("input,i", po::value<std::string>(),
                     "Путь до входного файла")(
      "threshold, t", po::value<float>(), "Минимальное число")("help",
                                                               "this message");
  po::positional_options_description positionalDescription;
  positionalDescription.add("input", -1);
  po::variables_map map;
  try {
    po::store(po::command_line_parser(argc, argv)
                  .options(desc)
                  .positional(positionalDescription)
                  .run(),
              map);
    po::store(po::parse_command_line(argc, argv, desc), map);
    po::notify(map);
    if (map.count("help")) {
      std::cout << "Usage: options_description [options]\n";
      std::cout << desc;
      return false;
    }
    if (map.count("threshold"))
      data->threshold = map["threshold"].as<float>();
    else
      data->threshold = 0.1;
    if (map.count("input"))
      data->inp_path = map["input"].as<std::string>();
    else
      data->inp_path = "../media/data,txt";
  } catch (std::exception& e) {
    std::cerr << "error: " << e.what();
    return false;
  }
  return true;
}


