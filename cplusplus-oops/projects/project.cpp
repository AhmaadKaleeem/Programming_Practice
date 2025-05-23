class Staff : public Person {
private:
    string staffid;
    string designation;
public:
   Staff(){
    staffid = "Not Specified ";
    designation = "Not Specified";
   }
   void setData(string name, int age,long long cnic,string staffid) {
        set_basic_info(name,age,cnic);
        this-> staffid = staffid;
    }
   void setData(string name, int age,long long cnic,string designation){
        set_basic_info(name,age,cnic);
        this -> designation = designation; 
    }
  
    void setdata(string name,int age,long long cnic,string staffid , string designation){
        set_basic_info(name,age,cnic);
        this-> staffid = staffid;
        this -> designation = designation; 
    }