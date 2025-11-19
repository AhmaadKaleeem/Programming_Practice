#include "voter.h"
#include <libraries.h>
using namespace std;
// Constuuctor
char province_name;
Voter::Voter() : voter_age(0), voter_name("Null"), voter_password("Null"), check_vote(false), voter_cnic("Null"), next(nullptr), provisional_p(0), na(0)
{
  voter_id = auto_generate_voter_id();
}

void Voter::register_voter()
{
  cout << "--- Registering Voter ---\n";

  cout << "Enter Name: ";
  cin.ignore();
  getline(cin, voter_name);

  input_cnic();

  cout << "Enter Age: ";
  cin >> voter_age;

  while (!validate_age())
  {
    cout << "Re-enter Age: ";
    cin >> voter_age;
  }

  cout << "\n === National Assembly Seat Number ===\n";
  cout << "Enter NA - ";
  cin >> na;
  while (!validate_national_assembly_seat(na))
  {
    cout << "Please Enter Valid NA\n";
    cout << "Enter NA - ";
    cin >> na;
  }

  bool flag = true;
  while (flag)
  {
    cout << "Select Province:\n";
    cout << "1. Punjab\n2. Sindh\n3. KPK\n4. Balochistan\n";
    int p_choice;
    cin >> p_choice;
    if (cin.fail())
    {
      cin.clear();            // clear error flag
      cin.ignore(1000, '\n'); // discard invalid input
      cout << "Invalid input. Please enter a number.\n";
      continue;
    }
    switch (p_choice)
    {
    case 1:
      province = PUNJAB;
      province_name = 'P';
      this->selected_area = &pp_area_names;
      flag = false;
      break;
    case 2:
      province = SINDH;
      province_name = 'S';
      this->selected_area = &ps_area_names;
      flag = false;
      break;
    case 3:
      province = KPK;
      province_name = 'K';
      this->selected_area = &pk_area_names;
      flag = false;
      break;
    case 4:
      province = BALOCHISTAN;
      province_name = 'B';
      this->selected_area = &pb_area_names;
      flag = false;
      break;
    default:
      cout << "Invalid province choice!\n";
      break;
    }
  }

  cout << "\n === Provincial Assembly Seat Number ===\n";
  cout << "Enter P" << province_name << " - ";
  cin >> provisional_p;
  while (!validate_provincial_seat(province, provisional_p))
  {
    cout << "Please Enter Valid P" << province_name << "\n";
    cout << "Enter P" << province_name << " - ";
    cin >> provisional_p;
  }

  cout << "Set Password: ";
  cin.ignore();
  getline(cin, voter_password);

  voter_id = auto_generate_voter_id();

  cout << "Voter Registered Successfully!\n";
  display_voter();
}

bool Voter::validate_national_assembly_seat(int seat_no)
{
  if (seat_no <= 0 || seat_no >= 267)
  {
    return false;
  }
  return true;
}

bool Voter::validate_provincial_seat(Province p, int seat_no)
{
  switch (p)
  {
  case PUNJAB:
    if (seat_no <= 0 || seat_no >= 298)
    {
      return false;
    }
    return true;

  case SINDH:
    if (seat_no <= 0 || seat_no >= 169)
    {
      return false;
    }
    return true;

  case KPK:
    if (seat_no <= 0 || seat_no >= 116)
    {
      return false;
    }
    return true;

  case BALOCHISTAN:
    if (seat_no <= 0 || seat_no >= 52)
    {
      return false;
    }
    return true;

  default:
    return false;
    break;
  }
}

string Voter::auto_generate_voter_id()
{
  hash<string> hash_voterid;
  size_t hash_value = hash_voterid(voter_cnic); // Hashing cnic as cnic will be unique
  hash_value = hash_value % 100000;
  return "VTR" + to_string(hash_value);
}

bool Voter::validate_age()
{
  if (voter_age >= 18)
  {
    return true;
  }
  else
  {
    cout << "Error! Voter Must Be At Least 18 Year Old\n";
    return false;
  }
}

bool Voter::validate_cnic()
{
  if (voter_cnic.length() != 13)
  {
    cout << "Error! CNIC Must Consist Of 13 Digits\n";
    return false;
  }
  else
  {
    for (char c : voter_cnic)
    {
      if (c < '0' || c > '9')
      {
        cout << "Error! CNIC Must Consist of 13 Digits\n";
        return false;
      }
    }
    return true;
  }
}

void Voter::input_cnic()
{
  do
  {
    cout << "Enter Your CNIC: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, voter_cnic);
  } while (!validate_cnic());
}

void Voter::display_voter()
{
  cout << "============================================= Voter Information =============================================\n";
  cout << "Name -> " << setw(5) << voter_name << "\nID -> " << setw(5) << voter_id << "\n";
  cout << "CNIC -> " << setw(5) << voter_cnic << "\nAge -> " << setw(5) << voter_age << "\n";
  cout << "Province -> " << setw(5) << province << "\nCasted Vote -> " << setw(5) << (check_vote ? "Yes" : "No") << "\n";
  cout << "NA -> " << na << setw(10) << "Area -> " << na_area_names[na] << "\n";
  if (selected_area != nullptr)
  {
    if (selected_area->find(provisional_p) != selected_area->end())
      cout << "P" << province_name << " -> " << provisional_p
           << setw(10) << "Area -> " << (*selected_area)[provisional_p] << "\n";
    else
      cout << "P" << province_name << " -> " << provisional_p
           << setw(10) << "Area -> Not Found\n";
  }
}

unordered_map<int, string> Voter::na_area_names = {
    // Khyber Pakhtunkhwa
    {1, "Chitral Upper-cum-Chitral Lower"},
    {2, "Swat-I"},
    {3, "Swat-II"},
    {4, "Swat-III"},
    {5, "Upper Dir"},
    {6, "Lower Dir-I"},
    {7, "Lower Dir-II"},
    {8, "Bajaur"},
    {9, "Malakand"},
    {10, "Buner"},
    {11, "Shangla"},
    {12, "Kohistan-cum-Lower Kohistan-cum-Kolai Palas"},
    {13, "Battagram"},
    {14, "Mansehra-I"},
    {15, "Mansehra-cum-Torghar"},
    {16, "Abbottabad-I"},
    {17, "Abbottabad-II"},
    {18, "Haripur"},
    {19, "Swabi-I"},
    {20, "Swabi-II"},
    {21, "Mardan-I"},
    {22, "Mardan-II"},
    {23, "Mardan-III"},
    {24, "Charsadda-I"},
    {25, "Charsadda-II"},
    {26, "Mohmand"},
    {27, "Khyber"},
    {28, "Peshawar-I"},
    {29, "Peshawar-II"},
    {30, "Peshawar-III"},
    {31, "Peshawar-IV"},
    {32, "Peshawar-V"},
    {33, "Nowshera-I"},
    {34, "Nowshera-II"},
    {35, "Kohat"},
    {36, "Hangu-cum-Orakzai"},
    {37, "Kurram"},
    {38, "Karak"},
    {39, "Bannu"},
    {40, "North Waziristan"},
    {41, "Lakki Marwat"},
    {42, "South Waziristan Upper-cum-South Waziristan Lower"},
    {43, "Tank-cum-Dera Ismail Khan"},
    {44, "Dera Ismail Khan-I"},
    {45, "Dera Ismail Khan-II"},

    // Islamabad Capital Territory
    {46, "Islamabad-I"},
    {47, "Islamabad-II"},
    {48, "Islamabad-III"},

    // Punjab
    {49, "Attock-I"},
    {50, "Attock-II"},
    {51, "Murree-cum-Rawalpindi"},
    {52, "Rawalpindi-I"},
    {53, "Rawalpindi-II"},
    {54, "Rawalpindi-III"},
    {55, "Rawalpindi-IV"},
    {56, "Rawalpindi-V"},
    {57, "Rawalpindi-VI"},
    {58, "Chakwal"},
    {59, "Talagang-cum-Chakwal"},
    {60, "Jhelum-I"},
    {61, "Jhelum-II"},
    {62, "Gujrat-I"},
    {63, "Gujrat-II"},
    {64, "Gujrat-III"},
    {65, "Gujrat-IV"},
    {66, "Wazirabad"},
    {67, "Hafizabad"},
    {68, "Mandi Bahauddin-I"},
    {69, "Mandi Bahauddin-II"},
    {70, "Sialkot-I"},
    {71, "Sialkot-II"},
    {72, "Sialkot-III"},
    {73, "Sialkot-IV"},
    {74, "Sialkot-V"},
    {75, "Narowal-I"},
    {76, "Narowal-II"},
    {77, "Gujranwala-I"},
    {78, "Gujranwala-II"},
    {79, "Gujranwala-III"},
    {80, "Gujranwala-IV"},
    {81, "Gujranwala-cum-Hafizabad"},
    {82, "Sargodha-I"},
    {83, "Sargodha-II"},
    {84, "Sargodha-III"},
    {85, "Sargodha-IV"},
    {86, "Sargodha-V"},
    {87, "Khushab-I"},
    {88, "Khushab-II"},
    {89, "Mianwali-I"},
    {90, "Mianwali-II"},
    {91, "Bhakkar-I"},
    {92, "Bhakkar-II"},
    {93, "Chiniot-I"},
    {94, "Chiniot-II"},
    {95, "Faisalabad-I"},
    {96, "Faisalabad-II"},
    {97, "Faisalabad-III"},
    {98, "Faisalabad-IV"},
    {99, "Faisalabad-V"},
    {100, "Faisalabad-VI"},
    {101, "Faisalabad-VII"},
    {102, "Faisalabad-VIII"},
    {103, "Faisalabad-IX"},
    {104, "Faisalabad-X"},
    {105, "Toba Tek Singh-I"},
    {106, "Toba Tek Singh-II"},
    {107, "Toba Tek Singh-III"},
    {108, "Jhang-I"},
    {109, "Jhang-II"},
    {110, "Jhang-III"},
    {111, "Nankana Sahib-I"},
    {112, "Nankana Sahib-II"},
    {113, "Sheikhupura-I"},
    {114, "Sheikhupura-II"},
    {115, "Sheikhupura-III"},
    {116, "Sheikhupura-IV"},
    {117, "Lahore-I"},
    {118, "Lahore-II"},
    {119, "Lahore-III"},
    {120, "Lahore-IV"},
    {121, "Lahore-V"},
    {122, "Lahore-VI"},
    {123, "Lahore-VII"},
    {124, "Lahore-VIII"},
    {125, "Lahore-IX"},
    {126, "Lahore-X"},
    {127, "Lahore-XI"},
    {128, "Lahore-XII"},
    {129, "Lahore-XIII"},
    {130, "Lahore-XIV"},
    {131, "Kasur-I"},
    {132, "Kasur-II"},
    {133, "Kasur-III"},
    {134, "Kasur-IV"},
    {135, "Okara-I"},
    {136, "Okara-II"},
    {137, "Okara-III"},
    {138, "Okara-IV"},
    {139, "Pakpattan-I"},
    {140, "Pakpattan-II"},
    {141, "Sahiwal-I"},
    {142, "Sahiwal-II"},
    {143, "Sahiwal-III"},
    {144, "Khanewal-I"},
    {145, "Khanewal-II"},
    {146, "Khanewal-III"},
    {147, "Khanewal-IV"},
    {148, "Multan-I"},
    {149, "Multan-II"},
    {150, "Multan-III"},
    {151, "Multan-IV"},
    {152, "Multan-V"},
    {153, "Multan-VI"},
    {154, "Lodhran-I"},
    {155, "Lodhran-II"},
    {156, "Vehari-I"},
    {157, "Vehari-II"},
    {158, "Vehari-III"},
    {159, "Vehari-IV"},
    {160, "Bahawalnagar-I"},
    {161, "Bahawalnagar-II"},
    {162, "Bahawalnagar-III"},
    {163, "Bahawalnagar-IV"},
    {164, "Bahawalpur-I"},
    {165, "Bahawalpur-II"},
    {166, "Bahawalpur-III"},
    {167, "Bahawalpur-IV"},
    {168, "Bahawalpur-V"},
    {169, "Rahim Yar Khan-I"},
    {170, "Rahim Yar Khan-II"},
    {171, "Rahim Yar Khan-III"},
    {172, "Rahim Yar Khan-IV"},
    {173, "Rahim Yar Khan-V"},
    {174, "Rahim Yar Khan-VI"},
    {175, "Muzaffargarh-I"},
    {176, "Muzaffargarh-II"},
    {177, "Muzaffargarh-III"},
    {178, "Muzaffargarh-IV"},
    {179, "Kot Addu-I"},
    {180, "Kot Addu-II"},
    {181, "Layyah-I"},
    {182, "Layyah-II"},
    {183, "Taunsa"},
    {184, "Dera Ghazi Khan-I"},
    {185, "Dera Ghazi Khan-II"},
    {186, "Dera Ghazi Khan-III"},
    {187, "Rajanpur-I"},
    {188, "Rajanpur-II"},
    {189, "Rajanpur-III"},

    // Sindh
    {190, "Jacobabad"},
    {191, "Kashmore"},
    {192, "Kashmore-cum-Shikarpur"},
    {193, "Shikarpur"},
    {194, "Larkana-I"},
    {195, "Larkana-II"},
    {196, "Qambar Shahdadkot-I"},
    {197, "Qambar Shahdadkot-II"},
    {198, "Ghotki-I"},
    {199, "Ghotki-II"},
    {200, "Sukkur-I"},
    {201, "Sukkur-II"},
    {202, "Khairpur-I"},
    {203, "Khairpur-II"},
    {204, "Khairpur-III"},
    {205, "Naushahro Feroze-I"},
    {206, "Naushahro Feroze-II"},
    {207, "Shaheed Benazirabad-I"},
    {208, "Shaheed Benazirabad-II"},
    {209, "Sanghar-I"},
    {210, "Sanghar-II"},
    {211, "Mirpur Khas-I"},
    {212, "Mirpur Khas-II"},
    {213, "Umerkot"},
    {214, "Tharparkar-I"},
    {215, "Tharparkar-II"},
    {216, "Matiari"},
    {217, "Tando Allahyar"},
    {218, "Hyderabad-I"},
    {219, "Hyderabad-II"},
    {220, "Hyderabad-III"},
    {221, "Tando Muhammad Khan"},
    {222, "Badin-I"},
    {223, "Badin-II"},
    {224, "Sujawal"},
    {225, "Thatta"},
    {226, "Jamshoro"},
    {227, "Dadu-I"},
    {228, "Dadu-II"},
    {229, "Malir-I (Karachi)"},
    {230, "Malir-II (Karachi)"},
    {231, "Malir-III (Karachi)"},
    {232, "Korangi-I (Karachi)"},
    {233, "Korangi-II (Karachi)"},
    {234, "Korangi-III (Karachi)"},
    {235, "Karachi East-I"},
    {236, "Karachi East-II"},
    {237, "Karachi East-III"},
    {238, "Karachi East-IV"},
    {239, "Karachi South-I"},
    {240, "Karachi South-II"},
    {241, "Karachi South-III"},
    {242, "Keamari-I (Karachi)"},
    {243, "Keamari-II (Karachi)"},
    {244, "Karachi West-I"},
    {245, "Karachi West-II"},
    {246, "Karachi West-III"},
    {247, "Karachi Central-I"},
    {248, "Karachi Central-II"},
    {249, "Karachi Central-III"},
    {250, "Karachi Central-IV"},

    // Balochistan (2024)
    {251, "Sherani-cum-Zhob-cum-Killa Saifullah"},
    {252, "Musakhel-cum-Barkhan-cum-Loralai-cum-Dukki"},
    {253, "Harnai-cum-Sibi-cum-Kohlu-cum-Dera Bugti"},
    {254, "Nasirabad-cum-Kachhi-cum-Jhal Magsi"},
    {255, "Sohbatpur-cum-Jaffarabad-cum-Usta Muhammad"},
    {256, "Khuzdar"},
    {257, "Hub-cum-Lasbela-cum-Awaran"},
    {258, "Panjgur-cum-Kech"},
    {259, "Kech-cum-Gwadar"},
    {260, "Chagai-cum-Nushki-cum-Kharan-cum-Washuk"},
    {261, "Surab-cum-Kalat-cum-Mastung"},
    {262, "Quetta-I"},
    {263, "Quetta-II"},
    {264, "Quetta-III"},
    {265, "Pishin"},
    {266, "Killa Abdullah-cum-Chaman"}};

unordered_map<int, string> Voter::pp_area_names = {
    {1, "Attock-I"},
    {2, "Attock-II"},
    {3, "Attock-III"},
    {4, "Attock-IV"},
    {5, "Attock-V"},
    {6, "Murree"},
    {7, "Rawalpindi-I"},
    {8, "Rawalpindi-II"},
    {9, "Rawalpindi-III"},
    {10, "Rawalpindi-IV"},
    {11, "Rawalpindi-V"},
    {12, "Rawalpindi-VI"},
    {13, "Rawalpindi-VII"},
    {14, "Rawalpindi-VIII"},
    {15, "Rawalpindi-IX"},
    {16, "Rawalpindi-X"},
    {17, "Rawalpindi-XI"},
    {18, "Rawalpindi-XII"},
    {19, "Rawalpindi-XIII"},
    {20, "Chakwal-I"},
    {21, "Chakwal-II"},
    {22, "Chakwal-cum-Talagang"},
    {23, "Talagang"},
    {24, "Jhelum-I"},
    {25, "Jhelum-II"},
    {26, "Jhelum-III"},
    {27, "Gujrat-I"},
    {28, "Gujrat-II"},
    {29, "Gujrat-III"},
    {30, "Gujrat-IV"},
    {31, "Gujrat-V"},
    {32, "Gujrat-VI"},
    {33, "Gujrat-VII"},
    {34, "Gujrat-VIII"},
    {35, "Wazirabad-I"},
    {36, "Wazirabad-II"},
    {37, "Hafizabad-I"},
    {38, "Hafizabad-II"},
    {39, "Hafizabad-III"},
    {40, "Mandi Bahauddin-I"},
    {41, "Mandi Bahauddin-II"},
    {42, "Mandi Bahauddin-III"},
    {43, "Mandi Bahauddin-IV"},
    {44, "Sialkot-I"},
    {45, "Sialkot-II"},
    {46, "Sialkot-III"},
    {47, "Sialkot-IV"},
    {48, "Sialkot-V"},
    {49, "Sialkot-VI"},
    {50, "Sialkot-VII"},
    {51, "Sialkot-VIII"},
    {52, "Sialkot-IX"},
    {53, "Sialkot-X"},
    {54, "Narowal-I"},
    {55, "Narowal-II"},
    {56, "Narowal-III"},
    {57, "Narowal-IV"},
    {58, "Narowal-V"},
    {59, "Gujranwala-I"},
    {60, "Gujranwala-II"},
    {61, "Gujranwala-III"},
    {62, "Gujranwala-IV"},
    {63, "Gujranwala-V"},
    {64, "Gujranwala-VI"},
    {65, "Gujranwala-VII"},
    {66, "Gujranwala-VIII"},
    {67, "Gujranwala-IX"},
    {68, "Gujranwala-X"},
    {69, "Gujranwala-XI"},
    {70, "Gujranwala-XII"},
    {71, "Sargodha-I"},
    {72, "Sargodha-II"},
    {73, "Sargodha-III"},
    {74, "Sargodha-IV"},
    {75, "Sargodha-V"},
    {76, "Sargodha-VI"},
    {77, "Sargodha-VII"},
    {78, "Sargodha-VIII"},
    {79, "Sargodha-IX"},
    {80, "Sargodha-X"},
    {81, "Khushab-I"},
    {82, "Khushab-II"},
    {83, "Khushab-III"},
    {84, "Khushab-IV"},
    {85, "Mianwali-I"},
    {86, "Mianwali-II"},
    {87, "Mianwali-III"},
    {88, "Mianwali-IV"},
    {89, "Bhakkar-I"},
    {90, "Bhakkar-II"},
    {91, "Bhakkar-III"},
    {92, "Bhakkar-IV"},
    {93, "Chiniot-I"},
    {94, "Chiniot-II"},
    {95, "Chiniot-III"},
    {96, "Chiniot-IV"},
    {97, "Faisalabad-I"},
    {98, "Faisalabad-II"},
    {99, "Faisalabad-III"},
    {100, "Faisalabad-IV"},
    {101, "Faisalabad-V"},
    {102, "Faisalabad-VI"},
    {103, "Faisalabad-VII"},
    {104, "Faisalabad-VIII"},
    {105, "Faisalabad-IX"},
    {106, "Faisalabad-X"},
    {107, "Faisalabad-XI"},
    {108, "Faisalabad-XII"},
    {109, "Faisalabad-XIII"},
    {110, "Faisalabad-XIV"},
    {111, "Faisalabad-XV"},
    {112, "Faisalabad-XVI"},
    {113, "Faisalabad-XVII"},
    {114, "Faisalabad-XVIII"},
    {115, "Faisalabad-XIX"},
    {116, "Faisalabad-XX"},
    {117, "Faisalabad-XXI"},
    {118, "Faisalabad-XXII"},
    {119, "Toba Tek Singh-I"},
    {120, "Toba Tek Singh-II"},
    {121, "Toba Tek Singh-III"},
    {122, "Toba Tek Singh-IV"},
    {123, "Toba Tek Singh-V"},
    {124, "Toba Tek Singh-VI"},
    {125, "Jhang-I"},
    {126, "Jhang-II"},
    {127, "Jhang-III"},
    {128, "Jhang-IV"},
    {129, "Jhang-V"},
    {130, "Jhang-VI"},
    {131, "Jhang-VII"},
    {132, "Nankana Sahib-I"},
    {133, "Nankana Sahib-II"},
    {134, "Nankana Sahib-III"},
    {135, "Nankana Sahib-IV"},
    {136, "Sheikhupura-I"},
    {137, "Sheikhupura-II"},
    {138, "Sheikhupura-III"},
    {139, "Sheikhupura-IV"},
    {140, "Sheikhupura-V"},
    {141, "Sheikhupura-VI"},
    {142, "Sheikhupura-VII"},
    {143, "Sheikhupura-VIII"},
    {144, "Sheikhupura-IX"},
    {145, "Lahore-I"},
    {146, "Lahore-II"},
    {147, "Lahore-III"},
    {148, "Lahore-IV"},
    {149, "Lahore-V"},
    {150, "Lahore-VI"},
    {151, "Lahore-VII"},
    {152, "Lahore-VIII"},
    {153, "Lahore-IX"},
    {154, "Lahore-X"},
    {155, "Lahore-XI"},
    {156, "Lahore-XII"},
    {157, "Lahore-XIII"},
    {158, "Lahore-XIV"},
    {159, "Lahore-XV"},
    {160, "Lahore-XVI"},
    {161, "Lahore-XVII"},
    {162, "Lahore-XVIII"},
    {163, "Lahore-XIX"},
    {164, "Lahore-XX"},
    {165, "Lahore-XXI"},
    {166, "Lahore-XXII"},
    {167, "Lahore-XXIII"},
    {168, "Lahore-XXIV"},
    {169, "Lahore-XXV"},
    {170, "Lahore-XXVI"},
    {171, "Lahore-XXVII"},
    {172, "Lahore-XXVIII"},
    {173, "Lahore-XXIX"},
    {174, "Lahore-XXX"},
    {175, "Kasur-I"},
    {176, "Kasur-II"},
    {177, "Kasur-III"},
    {178, "Kasur-IV"},
    {179, "Kasur-V"},
    {180, "Kasur-VI"},
    {181, "Kasur-VII"},
    {182, "Kasur-VIII"},
    {183, "Kasur-IX"},
    {184, "Kasur-X"},
    {185, "Okara-I"},
    {186, "Okara-II"},
    {187, "Okara-III"},
    {188, "Okara-IV"},
    {189, "Okara-V"},
    {190, "Okara-VI"},
    {191, "Okara-VII"},
    {192, "Okara-VIII"},
    {193, "Pakpattan-I"},
    {194, "Pakpattan-II"},
    {195, "Pakpattan-III"},
    {196, "Pakpattan-IV"},
    {197, "Pakpattan-V"},
    {198, "Sahiwal-I"},
    {199, "Sahiwal-II"},
    {200, "Sahiwal-III"},
    {201, "Sahiwal-IV"},
    {202, "Sahiwal-V"},
    {203, "Sahiwal-VI"},
    {204, "Sahiwal-VII"},
    {205, "Khanewal-I"},
    {206, "Khanewal-II"},
    {207, "Khanewal-III"},
    {208, "Khanewal-IV"},
    {209, "Khanewal-V"},
    {210, "Khanewal-VI"},
    {211, "Khanewal-VII"},
    {212, "Khanewal-VIII"},
    {213, "Multan-I"},
    {214, "Multan-II"},
    {215, "Multan-III"},
    {216, "Multan-IV"},
    {217, "Multan-V"},
    {218, "Multan-VI"},
    {219, "Multan-VII"},
    {220, "Multan-VIII"},
    {221, "Multan-IX"},
    {222, "Multan-X"},
    {223, "Multan-XI"},
    {224, "Multan-XII"},
    {225, "Multan-XIII"},
    {226, "Multan-XIV"},
    {227, "Multan-XV"},
    {228, "Multan-XVI"},
    {229, "Lodhran-I"},
    {230, "Lodhran-II"},
    {231, "Lodhran-III"},
    {232, "Lodhran-IV"},
    {233, "Lodhran-V"},
    {234, "Lodhran-VI"},
    {235, "Vehari-I"},
    {236, "Vehari-II"},
    {237, "Vehari-III"},
    {238, "Vehari-IV"},
    {239, "Vehari-V"},
    {240, "Vehari-VI"},
    {241, "Vehari-VII"},
    {242, "Vehari-VIII"},
    {243, "Bahawalnagar-I"},
    {244, "Bahawalnagar-II"},
    {245, "Bahawalnagar-III"},
    {246, "Bahawalnagar-IV"},
    {247, "Bahawalnagar-V"},
    {248, "Bahawalnagar-VI"},
    {249, "Bahawalnagar-VII"},
    {250, "Bahawalnagar-VIII"},
    {251, "Bahawalpur-I"},
    {252, "Bahawalpur-II"},
    {253, "Bahawalpur-III"},
    {254, "Bahawalpur-IV"},
    {255, "Bahawalpur-V"},
    {256, "Bahawalpur-VI"},
    {257, "Bahawalpur-VII"},
    {258, "Bahawalpur-VIII"},
    {259, "Bahawalpur-IX"},
    {260, "Bahawalpur-X"},
    {261, "Rahim Yar Khan-I"},
    {262, "Rahim Yar Khan-II"},
    {263, "Rahim Yar Khan-III"},
    {264, "Rahim Yar Khan-IV"},
    {265, "Rahim Yar Khan-V"},
    {266, "Rahim Yar Khan-VI"},
    {267, "Rahim Yar Khan-VII"},
    {268, "Rahim Yar Khan-VIII"},
    {269, "Rahim Yar Khan-IX"},
    {270, "Rahim Yar Khan-X"},
    {271, "Rahim Yar Khan-XI"},
    {272, "Rahim Yar Khan-XII"},
    {273, "Rahim Yar Khan-XIII"},
    {274, "Muzaffargarh-I"},
    {275, "Muzaffargarh-II"},
    {276, "Muzaffargarh-III"},
    {277, "Muzaffargarh-IV"},
    {278, "Muzaffargarh-V"},
    {279, "Kot Addu-I"},
    {280, "Kot Addu-II"},
    {281, "Kot Addu-III"},
    {282, "Layyah-I"},
    {283, "Layyah-II"},
    {284, "Layyah-III"},
    {285, "Layyah-IV"},
    {286, "Layyah-V"},
    {287, "Taunsa"},
    {288, "Dera Ghazi Khan-I"},
    {289, "Dera Ghazi Khan-II"},
    {290, "Dera Ghazi Khan-III"},
    {291, "Dera Ghazi Khan-IV"},
    {292, "Dera Ghazi Khan-V"},
    {293, "Dera Ghazi Khan-VI"},
    {294, "Rajanpur-I"},
    {295, "Rajanpur-II"},
    {296, "Rajanpur-III"},
    {297, "Rajanpur-IV"}

};

unordered_map<int, string> Voter::ps_area_names = {
    {1, "Jacobabad-I"},
    {2, "Jacobabad-II"},
    {3, "Jacobabad-III"},
    {4, "Kashmore-I"},
    {5, "Kashmore-II"},
    {6, "Kashmore-III"},
    {7, "Shikarpur-I"},
    {8, "Shikarpur-II"},
    {9, "Shikarpur-III"},
    {10, "Larkana-I"},
    {11, "Larkana-II"},
    {12, "Larkana-III"},
    {13, "Larkana-IV"},
    {14, "Qambar Shahdadkot-I"},
    {15, "Qambar Shahdadkot-II"},
    {16, "Qambar Shahdadkot-III"},
    {17, "Qambar Shahdadkot-IV"},
    {18, "Ghotki-I"},
    {19, "Ghotki-II"},
    {20, "Ghotki-III"},
    {21, "Ghotki-IV"},
    {22, "Sukkur-I"},
    {23, "Sukkur-II"},
    {24, "Sukkur-III"},
    {25, "Sukkur-IV"},
    {26, "Khairpur-I"},
    {27, "Khairpur-II"},
    {28, "Khairpur-III"},
    {29, "Khairpur-IV"},
    {30, "Khairpur-V"},
    {31, "Khairpur-VI"},
    {32, "Naushahro Feroze-I"},
    {33, "Naushahro Feroze-II"},
    {34, "Naushahro Feroze-III"},
    {35, "Naushahro Feroze-IV"},
    {36, "Shaheed Benazirabad-I"},
    {37, "Shaheed Benazirabad-II"},
    {38, "Shaheed Benazirabad-III"},
    {39, "Shaheed Benazirabad-IV"},
    {40, "Sanghar-I"},
    {41, "Sanghar-II"},
    {42, "Sanghar-III"},
    {43, "Sanghar-IV"},
    {44, "Sanghar-V"},
    {45, "Sanghar-VI"},
    {46, "Mirpur Khas-I"},
    {47, "Mirpur Khas-II"},
    {48, "Mirpur Khas-III"},
    {49, "Mirpur Khas-IV"},
    {50, "Umerkot-I"},
    {51, "Umerkot-II"},
    {52, "Tharparkar-I"},
    {53, "Tharparkar-II"},
    {54, "Tharparkar-III"},
    {55, "Tharparkar-IV"},
    {56, "Matiari-I"},
    {57, "Matiari-II"},
    {58, "Tando Allahyar-I"},
    {59, "Tando Allahyar-II"},
    {60, "Hyderabad-I"},
    {61, "Hyderabad-II"},
    {62, "Hyderabad-III"},
    {63, "Hyderabad-IV"},
    {64, "Hyderabad-V"},
    {65, "Hyderabad-VI"},
    {66, "Tando Muhammad Khan-I"},
    {67, "Tando Muhammad Khan-II"},
    {68, "Badin-I"},
    {69, "Badin-II"},
    {70, "Badin-III"},
    {71, "Badin-IV"},
    {72, "Badin-V"},
    {73, "Sujawal-I"},
    {74, "Sujawal-II"},
    {75, "Thatta-I"},
    {76, "Thatta-II"},
    {77, "Jamshoro-I"},
    {78, "Jamshoro-II"},
    {79, "Jamshoro-III"},
    {80, "Dadu-I"},
    {81, "Dadu-II"},
    {82, "Dadu-III"},
    {83, "Dadu-IV"},
    {84, "Malir-I (Karachi)"},
    {85, "Malir-II (Karachi)"},
    {86, "Malir-III (Karachi)"},
    {87, "Malir-IV (Karachi)"},
    {88, "Malir-V (Karachi)"},
    {89, "Malir-VI (Karachi)"},
    {90, "Korangi-I (Karachi)"},
    {91, "Korangi-II (Karachi)"},
    {92, "Korangi-III (Karachi)"},
    {93, "Korangi-IV (Karachi)"},
    {94, "Korangi-V (Karachi)"},
    {95, "Korangi-VI (Karachi)"},
    {96, "Korangi-VII (Karachi)"},
    {97, "Karachi East-I"},
    {98, "Karachi East-II"},
    {99, "Karachi East-III"},
    {100, "Karachi East-IV"},
    {101, "Karachi East-V"},
    {102, "Karachi East-VI"},
    {103, "Karachi East-VII"},
    {104, "Karachi East-VIII"},
    {105, "Karachi East-IX"},
    {106, "Karachi South-I"},
    {107, "Karachi South-II"},
    {108, "Karachi South-III"},
    {109, "Karachi South-IV"},
    {110, "Karachi South-V"},
    {111, "Keamari-I (Karachi)"},
    {112, "Keamari-II (Karachi)"},
    {113, "Keamari-III (Karachi)"},
    {114, "Keamari-IV (Karachi)"},
    {115, "Keamari-V (Karachi)"},
    {116, "Karachi West-I"},
    {117, "Karachi West-II"},
    {118, "Karachi West-III"},
    {119, "Karachi West-IV"},
    {120, "Karachi West-V"},
    {121, "Karachi West-VI"},
    {122, "Karachi Central-I"},
    {123, "Karachi Central-II"},
    {124, "Karachi Central-III"},
    {125, "Karachi Central-IV"},
    {126, "Karachi Central-V"},
    {127, "Karachi Central-VI"},
    {128, "Karachi Central-VII"},
    {129, "Karachi Central-VIII"},
    {130, "Karachi Central-IX"}};

unordered_map<int, string> Voter::pk_area_names = {
    {1, "Chitral Upper"},
    {2, "Chitral Lower"},
    {3, "Swat-I"},
    {4, "Swat-II"},
    {5, "Swat-III"},
    {6, "Swat-IV"},
    {7, "Swat-V"},
    {8, "Swat-VI"},
    {9, "Swat-VII"},
    {10, "Swat-VIII"},
    {11, "Upper Dir-I"},
    {12, "Upper Dir-II"},
    {13, "Upper Dir-III"},
    {14, "Lower Dir-I"},
    {15, "Lower Dir-II"},
    {16, "Lower Dir-III"},
    {17, "Lower Dir-IV"},
    {18, "Lower Dir-V"},
    {19, "Bajaur-I"},
    {20, "Bajaur-II"},
    {21, "Bajaur-III"},
    {22, "Bajaur-IV"},
    {23, "Malakand-I"},
    {24, "Malakand-II"},
    {25, "Buner-I"},
    {26, "Buner-II"},
    {27, "Buner-III"},
    {28, "Shangla-I"},
    {29, "Shangla-II"},
    {30, "Shangla-III"},
    {31, "Kohistan Upper"},
    {32, "Kohistan Lower"},
    {33, "Kolai Palas Kohistan"},
    {34, "Battagram-I"},
    {35, "Battagram-II"},
    {36, "Mansehra-I"},
    {37, "Mansehra-II"},
    {38, "Mansehra-III"},
    {39, "Mansehra-IV"},
    {40, "Mansehra-V"},
    {41, "Torghar"},
    {42, "Abbottabad-I"},
    {43, "Abbottabad-II"},
    {44, "Abbottabad-III"},
    {45, "Abbottabad-IV"},
    {46, "Haripur-I"},
    {47, "Haripur-II"},
    {48, "Haripur-III"},
    {49, "Swabi-I"},
    {50, "Swabi-II"},
    {51, "Swabi-III"},
    {52, "Swabi-IV"},
    {53, "Swabi-V"},
    {54, "Mardan-I"},
    {55, "Mardan-II"},
    {56, "Mardan-III"},
    {57, "Mardan-IV"},
    {58, "Mardan-V"},
    {59, "Mardan-VI"},
    {60, "Mardan-VII"},
    {61, "Mardan-VIII"},
    {62, "Charsadda-I"},
    {63, "Charsadda-II"},
    {64, "Charsadda-III"},
    {65, "Charsadda-IV"},
    {66, "Charsadda-V"},
    {67, "Mohmand-I"},
    {68, "Mohmand-II"},
    {69, "Khyber-I"},
    {70, "Khyber-II"},
    {71, "Khyber-III"},
    {72, "Peshawar-I"},
    {73, "Peshawar-II"},
    {74, "Peshawar-III"},
    {75, "Peshawar-IV"},
    {76, "Peshawar-V"},
    {77, "Peshawar-VI"},
    {78, "Peshawar-VII"},
    {79, "Peshawar-VIII"},
    {80, "Peshawar-IX"},
    {81, "Peshawar-X"},
    {82, "Peshawar-XI"},
    {83, "Peshawar-XII"},
    {84, "Peshawar-XIII"},
    {85, "Nowshera-I"},
    {86, "Nowshera-II"},
    {87, "Nowshera-III"},
    {88, "Nowshera-IV"},
    {89, "Nowshera-V"},
    {90, "Kohat-I"},
    {91, "Kohat-II"},
    {92, "Kohat-III"},
    {93, "Hangu"},
    {94, "Orakzai"},
    {95, "Kurram-I"},
    {96, "Kurram-II"},
    {97, "Karak-I"},
    {98, "Karak-II"},
    {99, "Bannu-I"},
    {100, "Bannu-II"},
    {101, "Bannu-III"},
    {102, "Bannu-IV"},
    {103, "North Waziristan-I"},
    {104, "North Waziristan-II"},
    {105, "Lakki Marwat-I"},
    {106, "Lakki Marwat-II"},
    {107, "Lakki Marwat-III"},
    {108, "Tank"},
    {109, "South Waziristan Upper"},
    {110, "South Waziristan Lower"},
    {111, "Dera Ismail Khan-I"},
    {112, "Dera Ismail Khan-II"},
    {113, "Dera Ismail Khan-III"},
    {114, "Dera Ismail Khan-IV"},
    {115, "Dera Ismail Khan-V"}};

unordered_map<int, string> Voter::pb_area_names = {
    {1, "Sherani-cum-Zhob"},
    {2, "Zhob"},
    {3, "Killa Saifullah"},
    {4, "Barkhan"},
    {5, "Loralai"},
    {6, "Duki"},
    {7, "Ziarat-cum-Harnai"},
    {8, "Sibi"},
    {9, "Kohlu"},
    {10, "Dera Bugti"},
    {11, "Jhal Magsi"},
    {12, "Kachhi"},
    {13, "Nasirabad-I"},
    {14, "Nasirabad-II"},
    {15, "Sohbatpur"},
    {16, "Jaffarabad-I"},
    {17, "Jaffarabad-II"},
    {18, "Khuzdar-I"},
    {19, "Khuzdar-II"},
    {20, "Khuzdar-III"},
    {21, "Hub"},
    {22, "Lasbela"},
    {23, "Awaran"},
    {24, "Gwadar"},
    {25, "Kech-I"},
    {26, "Kech-II"},
    {27, "Kech-III"},
    {28, "Kech-IV"},
    {29, "Panjgur-I"},
    {30, "Panjgur-II"},
    {31, "Washuk"},
    {32, "Chagai"},
    {33, "Kharan"},
    {34, "Nushki"},
    {35, "Surab"},
    {36, "Kalat"},
    {37, "Mastung"},
    {38, "Quetta-I"},
    {39, "Quetta-II"},
    {40, "Quetta-III"},
    {41, "Quetta-IV"},
    {42, "Quetta-V"},
    {43, "Quetta-VI"},
    {44, "Quetta-VII"},
    {45, "Quetta-VIII"},
    {46, "Quetta-IX"},
    {47, "Pishin-I"},
    {48, "Pishin-II"},
    {49, "Pishin-III"},
    {50, "Killa Abdullah"},
    {51, "Chaman"}};