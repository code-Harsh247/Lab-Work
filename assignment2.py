import tkinter as tk;
from tkinter import messagebox



class Person:
    def __init__(self, name, age, userID, password, profile_status, gender):
        self.name = name
        self.age = age
        self.user_ID = userID
        self.password = password
        self.profile_status = profile_status
        self.gender = gender
        self.tries = 3
        

class Teacher(Person):
    def __init__(self, name, user_ID, password, age, employee_id, department, profile_status, gender):
        super().__init__(name, age, user_ID, password, profile_status, gender)
        self.employee_id = employee_id
        self.department = department


class Student(Person):
    def __init__(self, name, age, student_id, user_ID, password, profile_status, gender):
        super().__init__(name, age, user_ID, password, profile_status, gender)
        self.student_id = student_id
        self.courses = []

class UndergraduateStudent(Student):
    def __init__(self, name, age, student_id, department, user_ID, password, profile_status, gender):
        super().__init__(name, age, student_id, user_ID, password, profile_status, gender)
        self.department = department



class PostgraduateStudent(Student):
    def __init__(self, name, age, student_id, research_area, user_ID, password, profile_status, gender):
        super().__init__(name, age, student_id,user_ID, password, profile_status, gender)
        self.research_area = research_area


header_font = ("Helvetica", 30, "italic bold")
btn_font = ("Helvetica", 15)
text_font = ("Helvetica", 15)


#--------- DataBase ---------#

teachers_list = []
PG_list =[]
UG_list =[]

#----------------------------#



class MyApp:

    def __init__(self, root):
        self.root = root
        self.root.title("Academic Unit")
        self.root.geometry("400x400")
        
        self.home_frame = tk.Frame(root)
        self.registration_frame = tk.Frame(root)
        self.sign_in_frame = tk.Frame(root)
        self.post_login_frame = tk.Frame(root)
        
        self.back_button = tk.Button(root, text="Back", command=self.go_back, font=btn_font, width=18, height=1)
        self.back_button.pack(side="bottom", pady=10)

        self.history = [] #store history of frames

        self.profile_type = None
        self.gender = None
        self.User = None

        self.create_home_page()
        self.create_registration_page()
        self.create_sign_in_page()
        self.show_home_page()

        # self.password_entry = None
        # self.user_id_entry = None
        # self.profile_type_radio = None

        self.error_label = None
        

    def show_frame(self, frame):
        # Hide all frames
        self.home_frame.pack_forget()
        self.registration_frame.pack_forget()
        self.sign_in_frame.pack_forget()

        # Show the specified frame
        frame.pack()

        # Update the history
        self.history.append(frame)




    def create_home_page(self):

        label = tk.Label(self.home_frame, text="Academic Unit", font = ("Helvetica", 30, "italic bold"))
        label.pack(pady=10)

        label = tk.Label(self.home_frame, text="Welcome", font = ("Helvetica", 10))
        label.pack(pady=10)

        register_button = tk.Button(self.home_frame, text="Register New User", command=self.show_registration_page,  width=18, height=1, font=btn_font)
        register_button.pack(pady=10)

        sign_in_btn = tk.Button(self.home_frame, text ="Sign in", command=self.show_sign_in_page, width=18, height=1, font=btn_font)
        sign_in_btn.pack(pady=10)

    def create_sign_in_page(self):

        user_id_label = tk.Label(self.sign_in_frame, text="User Id:", font=text_font)
        self.user_id_entry_signin= tk.Entry(self.sign_in_frame)

        password_label = tk.Label(self.sign_in_frame, text="Password:", font= text_font)
        self.password_entry_signin = tk.Entry(self.sign_in_frame, show="*")


        submit_button = tk.Button(self.sign_in_frame, text="Sign In", command=self.sign_in, width=18, height=1, font=btn_font)

        user_id_label.pack(pady=5)
        self.user_id_entry_signin.pack(pady=5)

        password_label.pack(pady=5)
        self.password_entry_signin.pack(pady=5)

        submit_button.pack(pady=10)

    def validate_password(self, password):
        print("Checking Password")
        # a) Check length
        if not (8 <= len(password) <= 12):
            print("Invalid Length "+ str(len(password)) )
            return False

        # b) Check for at least one upper case, one digit, and one lower case
        if not (any(char.isupper() for char in password) and
                any(char.isdigit() for char in password) and
                any(char.islower() for char in password)):
            print("Invalid case b")
            return False

        # c) Check for one or more special characters
        special_characters = set('!@#$%&*')
        if not any(char in special_characters for char in password):
            print("No special character")
            return False

        # d) Check for no blank space
        if ' ' in password:
            print("Space")
            return False

        # If all conditions are satisfied, the password is valid
        return True

    def create_registration_page(self):

        user_id_label = tk.Label(self.registration_frame, text="User Id:", font=text_font)
        self.user_id_entry_register = tk.Entry(self.registration_frame)
        password_label = tk.Label(self.registration_frame, text="Password:", font=text_font)
        self.password_entry_register = tk.Entry(self.registration_frame)

        user_name_label = tk.Label(self.registration_frame, text="Name :", font=text_font)
        self.user_name_entry = tk.Entry(self.registration_frame)
        user_age_label = tk.Label(self.registration_frame, text="Age :", font=text_font)
        self.user_age_entry = tk.Entry(self.registration_frame)

        gender_label = tk.Label(self.registration_frame, text="Gender", font=text_font)
        self.gender_radio = tk.StringVar(value="NULL")
        radio_male = tk.Radiobutton(self.registration_frame, text="Male", variable=self.gender_radio, value="Male", command=self.gender_radio_selected)
        radio_female = tk.Radiobutton(self.registration_frame, text="Female", variable=self.gender_radio, value="Female", command=self.gender_radio_selected)

        next_button = tk.Button(self.registration_frame, text="Next", command=self.next_registration, width=18, height=1, font=btn_font)

        profile_type_label = tk.Label(self.registration_frame, text="Profile type:", font=text_font)
        self.profile_type_radio = tk.IntVar()
        radio_teacher = tk.Radiobutton(self.registration_frame, text="Teacher", variable=self.profile_type_radio,value=1, command=self.profile_radio_btn_selected)
        radio_UG = tk.Radiobutton(self.registration_frame, text="UG Student", variable=self.profile_type_radio,value=2, command=self.profile_radio_btn_selected)
        radio_PG = tk.Radiobutton(self.registration_frame, text="PG Student", variable=self.profile_type_radio,value=3, command=self.profile_radio_btn_selected)


        user_id_label.grid(row=0, column = 0,sticky="w")
        self.user_id_entry_register.grid(row=0, column = 1)

        password_label.grid(row=1, column = 0,sticky="w")
        self.password_entry_register.grid(row=1, column = 1)

        user_name_label.grid(row=3, column=0, sticky="w")
        self.user_name_entry.grid(row=3, column=1)
        user_age_label.grid(row=4, column=0, sticky="w")
        self.user_age_entry.grid(row=4, column=1)

        gender_label.grid(row=5, column =0, sticky="w")
        radio_male.grid(row=5, column=1, sticky="w", padx=10)
        radio_female.grid(row=5, column=2, sticky="w", padx=10)


        profile_type_label.grid(row=7,column=0)
        radio_teacher.grid(row=7,column=1,sticky="w", padx=10)
        radio_PG.grid(row=8,column=1,sticky="w", padx=10)
        radio_UG.grid(row=9,column=1,sticky="w", padx=10)
        

        next_button.grid(row=11, column=0, columnspan=3, rowspan=3, sticky="nsew", pady=(50,0))
        self.registration_frame.grid_rowconfigure(11, weight=1)

    
    def gender_radio_selected(self):
        selectedOption = self.gender_radio.get()
        self.gender = selectedOption

    def profile_radio_btn_selected(self):
        selectedOption = self.profile_type_radio.get()
        if selectedOption == 1 :
            self.profile_type = "Teacher"

        if selectedOption == 2 :
            self.profile_type = "UG-Student"
        if selectedOption == 3 :
            self.profile_type = "PG-Student"

    def show_post_login_page(self):
        # Hide all frames
        self.home_frame.pack_forget()
        self.back_button.pack_forget()
        self.registration_frame.pack_forget()
        self.sign_in_frame.pack_forget()

        # Show the post-login frame
        self.post_login_frame.pack()

    def show_sign_in_page(self):

        self.home_frame.pack_forget()
        self.sign_in_frame.pack()
        self.show_frame(self.sign_in_frame)

    def show_home_page(self):

        self.registration_frame.pack_forget()
        self.home_frame.pack()
        self.show_frame(self.home_frame)

    def show_registration_page(self):

        self.home_frame.pack_forget()
        self.registration_frame.pack()
        self.show_frame(self.registration_frame)

    def next_registration(self):

        print(self.password_entry_register.get())
        # Validate password
        if not self.validate_password(self.password_entry_register.get()):
            error_text ="Invalid password. Please follow the password criteria."
            error_label = tk.Label(self.registration_frame, text=error_text, font = ("Helvetica", 10), fg="red")
            error_label.grid(row=6, column=0, columnspan=3, rowspan=3, sticky="nsew")
            return
        
        else :
            print("Moving to the next registration page!")

            if(self.profile_type == "Teacher"):
                details_window_teacher = tk.Toplevel(self.root)
                details_window_teacher.geometry("500x180")
                details_window_teacher.title("Enter additional details")

                employee_id_label = tk.Label(details_window_teacher, text="Employee ID:", font=text_font)
                employee_id_entry = tk.Entry(details_window_teacher)

                depart_label = tk.Label(details_window_teacher, text="Department:", font=text_font)
                depart_entry = tk.Entry(details_window_teacher)

                employee_id_label.grid(row=0, column=0, pady=(20,10))
                employee_id_entry.grid(row=0, column=1, pady=(20,10))
                depart_label.grid(row=1, column=0, pady=(10,20) )
                depart_entry.grid(row=1, column=1, pady=(10,20))

                submit_button = tk.Button(details_window_teacher, text="Submit", command=lambda: self.appendTeacherDetails(employee_id_entry, depart_entry), width=18, height=1, font=btn_font)
                submit_button.grid(row=3, column=0, sticky="nsew", pady=10, padx=50)


            if(self.profile_type == "UG-Student"):
                details_window_ug = tk.Toplevel(self.root)
                details_window_ug.geometry("500x180")
                details_window_ug.title("Enter additional details")
                dept_label = tk.Label(details_window_ug, text="Department:", font=text_font)
                dept_entry = tk.Entry(details_window_ug)
                roll_label = tk.Label(details_window_ug, text="Roll No:", font=text_font)
                roll_entry = tk.Entry(details_window_ug)

                dept_label.grid(row=0, column=0, pady=(20, 10))
                dept_entry.grid(row=0, column=1, pady=(20, 10))
                roll_label.grid(row=1, column=0, pady=(20, 10))
                roll_entry.grid(row=1, column=1, pady=(20, 10))

                submit_button_ug = tk.Button(details_window_ug, text="Submit", command=lambda: self.appendUGDetails(dept_entry, roll_entry), width=18, height=1, font=btn_font)
                submit_button_ug.grid(row=3, column=0, sticky="nsew", pady=10, padx=50)

            
            if(self.profile_type == "PG-Student"):
                details_window_pg = tk.Toplevel(self.root)
                details_window_pg.geometry("500x180")
                details_window_pg.title("Enter additional details")

                research_area_label = tk.Label(details_window_pg, text="Research Area:", font=text_font)
                research_area_entry = tk.Entry(details_window_pg)
                roll_label = tk.Label(details_window_pg, text="Roll No:", font=text_font)
                roll_entry = tk.Entry(details_window_pg)

                research_area_label.grid(row=0, column=0, pady=(20, 10))
                research_area_entry.grid(row=0, column=1, pady=(20, 10))
                roll_label.grid(row=1, column=0, pady=(20, 10))
                roll_entry.grid(row=1, column=1, pady=(20, 10))

                submit_button_pg = tk.Button(details_window_pg, text="Submit", command=lambda: self.appendPGDetails(research_area_entry,roll_entry), width=18, height=1, font=btn_font)
                submit_button_pg.grid(row=3, column=0, sticky="nsew", pady=10, padx=50)
            

    def appendUGDetails(self, dept_entry, roll_entry):
        name = self.user_name_entry.get()
        age = self.user_age_entry.get()
        password = self.password_entry_register.get()
        user_ID = self.user_id_entry_register.get()
        dept = dept_entry.get()
        roll = roll_entry.get()

        user_profile = Person(name, age, user_ID, password, "Active", self.gender)

        ug_profile = UndergraduateStudent(user_profile.name, user_profile.age, roll, dept, user_profile.user_ID, user_profile.password,user_profile.profile_status, self.gender)
        UG_list.append(ug_profile)
        print(ug_profile.name, ug_profile.age,ug_profile.student_id ,ug_profile.department, ug_profile.user_ID, ug_profile.password)

    def appendPGDetails(self, research_area_entry, roll_entry):
        name = self.user_name_entry.get()
        age = self.user_age_entry.get()
        password = self.password_entry_register.get()
        user_ID = self.user_id_entry_register.get()
        research_area = research_area_entry.get()
        roll = roll_entry.get()

        user_profile = Person(name, age, user_ID, password, "Active", self.gender)

        pg_profile = PostgraduateStudent(user_profile.name, user_profile.age, roll, research_area, user_profile.user_ID, user_profile.password, user_profile.profile_status, self.gender)
        PG_list.append(pg_profile)
        print(pg_profile.name, pg_profile.age,pg_profile.student_id, pg_profile.research_area, pg_profile.user_ID, pg_profile.password)

    def appendTeacherDetails(self, employee_id_entry, department_entry):
            
            name = self.user_name_entry.get()
            age = self.user_age_entry.get()
            password = self.password_entry_register.get()
            user_ID = self.user_id_entry_register.get()
            employee_id = employee_id_entry.get()
            department = department_entry.get()
            

            user_profile = Person(name, age, user_ID, password, "Active", self.gender)

            teacher_profile = Teacher(user_profile.name, user_profile.user_ID, user_profile.password, user_profile.age, employee_id, department, user_profile.profile_status, self.gender )
            teachers_list.append(teacher_profile)
            print(teacher_profile.name, teacher_profile.age, teacher_profile.department, teacher_profile.employee_id, teacher_profile.gender, teacher_profile.user_ID, teacher_profile.password, teacher_profile.tries)
    
    def logout(self):
        # Hide the post-login frame and show the home frame
        self.post_login_frame.pack_forget()
        self.back_button.pack(side="bottom", pady=10)
        self.show_home_page()
    
    def sign_in(self):
        password = self.password_entry_signin.get()
        user_ID = self.user_id_entry_signin.get()


        for teacher in teachers_list:
            print(teacher.user_ID)
            if(teacher.user_ID == user_ID):
                if(teacher.password == password and teacher.profile_status == "Active"):
                    teacher.tries = 3
                    print("Sign in successfull. Profile type - teacher")
                    self.User = teacher
                    self.create_post_login_page()
                    self.show_post_login_page()
                elif(teacher.password != password and teacher.profile_status == "Active"):
                    print("User found but incorrect password entered")
                    teacher.tries -= 1
                    if(teacher.tries < 0):
                        teacher.profile_status = "Deactivated"
                        self.deactivatedInfo()
                        print("That account has been deactivated.")
                    else:
                        self.incorrectPassword(teacher.tries)
                elif(teacher.password == password and teacher.profile_status != "Active"):
                    self.deactivatedInfo()
                    print("That account has been deactivated.")
            else:
                self.profileNotFound()
                print("No profile with that userID found.")

        for student in UG_list:
            if(student.user_ID == user_ID):
                if(student.password == password and student.profile_status == "Active"):
                    student.tries = 3
                    print("UG student found. Sign in successfull")
                    self.User = student
                    self.create_post_login_page()
                    self.show_post_login_page()
                elif(student.password != password and student.profile_status == "Active"):
                    print("User found but incorrect password entered")
                    student.tries -= 1
                    if(student.tries < 0):
                        student.profile_status = "Deactivated"
                        self.deactivatedInfo()
                        print("That account has been deactivated.")
                    else:
                        self.incorrectPassword()
                elif(student.password == password and student.profile_status != "Active"):
                    self.deactivatedInfo()
                    print("Deactivated")
            else:
                self.profileNotFound()
                print("No profile with that userID found.")

        
        for student in PG_list:
            if(student.user_ID == user_ID):
                if(student.password == password and student.profile_status == "Active"):
                    student.tries = 3
                    print("PG student found. Sign in successfull")
                    self.User = student
                    self.create_post_login_page()
                    self.show_post_login_page()
                elif(student.password != password and student.profile_status == "Active"):
                    print("User found but incorrect password entered")
                    student.tries -= 1
                    if(student.tries < 0):
                        student.profile_status = "Deactivated"
                        self.deactivatedInfo()
                        print("That account has been deactivated.")
                    else:
                        self.incorrectPassword(student)
                        
                elif(student.password == password and student.profile_status != "Active"):
                    self.deactivatedInfo()
                    print("That account has been deactivated.")
            else:
                self.profileNotFound()
                print("No profile with that userID found.")

    def create_post_login_page(self):
        
        
        # Create widgets for the post-login page
        welcome_label = tk.Label(self.post_login_frame, text="Welcome to the Academic Unit!", font=("Helvetica", 16))
        logout_button = tk.Button(self.post_login_frame, text="Logout", command=self.logout, font=btn_font)
        name_label = tk.Label(self.post_login_frame, text="Name :     ", font=("Helvetica", 10))
        user_id_label = tk.Label(self.post_login_frame, text="User ID :", font=("Helvetica", 10))
        age_id_label = tk.Label(self.post_login_frame, text="Age :", font=("Helvetica", 10))
        gender_label = tk.Label(self.post_login_frame, text="Gender :", font=("Helvetica", 10))
        profile_type_label = tk.Label(self.post_login_frame, text="Profile Type :", font=("Helvetica", 10))
        name = tk.Label(self.post_login_frame, text=self.User.name, font=("Helvetica", 10))
        user_id = tk.Label(self.post_login_frame, text=self.User.user_ID, font=("Helvetica", 10))
        age = tk.Label(self.post_login_frame, text=self.User.age,  font=("Helvetica", 10))
        gender = tk.Label(self.post_login_frame, text=self.User.gender, font=("Helvetica", 10))
        name_label.grid(row=1, column=0, sticky="e", padx=(20, 0))
        name.grid(row=1, column=1, sticky="w", padx=(0, 20))
        user_id_label.grid(row=2, column=0, sticky="e", padx=(20, 0))
        user_id.grid(row=2, column=1, sticky="w", padx=(0, 20))
        age_id_label.grid(row=3, column=0, sticky="e", padx=(20, 0))
        age.grid(row=3, column=1, sticky="w", padx=(0, 20))
        gender_label.grid(row=4, column=0, sticky="e", padx=(20, 0))
        gender.grid(row=4, column=1, sticky="w", padx=(0, 20))
        
        if isinstance(self.User,Teacher):
            department_label = tk.Label(self.post_login_frame, text="Department:", font=("Helvetica", 10))
            department = tk.Label(self.post_login_frame, text=self.User.department, font=("Helvetica", 10))
            employee_id_label = tk.Label(self.post_login_frame, text="Employee ID:", font=("Helvetica", 10))
            employee_id = tk.Label(self.post_login_frame, text=self.User.employee_id, font=("Helvetica", 10))
            profile_type = tk.Label(self.post_login_frame, text="Teacher", font=("Helvetica", 10))
            profile_type_label.grid(row=5, column=0, sticky="e", padx=(20, 0))
            profile_type.grid(row=5, column=1, sticky="w", padx=(0, 20))
            department_label.grid(row=6, column=0, sticky="e", padx=(20, 0))
            department.grid(row=6, column=1, sticky="w", padx=(0, 20))
            employee_id_label.grid(row=7, column=0, sticky="e", padx=(20, 0))
            employee_id.grid(row=7, column=1, sticky="w", padx=(0, 20))
        elif isinstance(self.User, UndergraduateStudent):
            department_label = tk.Label(self.post_login_frame, text="Department:", font=("Helvetica", 10))
            department = tk.Label(self.post_login_frame, text=self.User.department, font=("Helvetica", 10))
            roll_label = tk.Label(self.post_login_frame, text="Roll No:", font=("Helvetica", 10))
            roll = tk.Label(self.post_login_frame, text=self.User.student_id, font=("Helvetica", 10))
            profile_type = tk.Label(self.post_login_frame, text="Undergraduate Student", font=("Helvetica", 10))
            profile_type_label.grid(row=5, column=0, sticky="e", padx=(20, 0))
            profile_type.grid(row=5, column=1, sticky="w", padx=(0, 20))
            department_label.grid(row=6, column=0, sticky="e", padx=(20, 0))
            department.grid(row=6, column=1, sticky="w", padx=(0, 20))
            roll_label.grid(row=7, column=0, sticky="e", padx=(20, 0))
            roll.grid(row=7, column=1, sticky="w", padx=(0, 20))
        elif isinstance(self.User, PostgraduateStudent):
            research_area_label = tk.Label(self.post_login_frame, text="Research Area:", font=("Helvetica", 10))
            research_area = tk.Label(self.post_login_frame, text=self.User.research_area, font=("Helvetica", 10))
            roll_label = tk.Label(self.post_login_frame, text="Roll No:", font=("Helvetica", 10))
            roll = tk.Label(self.post_login_frame, text=self.User.student_id, font=("Helvetica", 10))
            profile_type = tk.Label(self.post_login_frame, text="Postgraduate Student", font=("Helvetica", 10))
            profile_type_label.grid(row=5, column=0, sticky="e", padx=(20, 0))
            profile_type.grid(row=5, column=1, sticky="w", padx=(0, 20))
            research_area_label.grid(row=6, column=0, sticky="e", padx=(20, 0))
            research_area.grid(row=6, column=1, sticky="w", padx=(0, 20))
            roll_label.grid(row=7, column=0, sticky="e", padx=(20, 0))
            roll.grid(row=7, column=1, sticky="w", padx=(0, 20))
        # Pack widgets
        welcome_label.grid(row=0, column=0, columnspan=2, pady=(20, 10))
        logout_button.grid(row=9, column=2, pady=(20, 10))

    def profileNotFound(self):
        messagebox.showerror("Profile Not found","No profile with the given user ID exist in the database")

    def deactivatedInfo(self):
        messagebox.showwarning("Account Deactivated", "Error signing in. The account has been deactivated")


    def incorrectPassword(self, tries_remaining):
        messagebox.showwarning("Incorrect Password", f"The user exists in the database but the entered password is incorrect. You have only {tries_remaining} tries remaining.")
    
    def go_back(self):
        # Check if there is a frame in the history
        if len(self.history) > 1:
            # Remove the current frame from the history
            current_frame = self.history.pop()
            
            # Show the previous frame
            previous_frame = self.history[-1]
            self.show_frame(previous_frame)

if __name__ == "__main__":
    root = tk.Tk()
    app = MyApp(root)

    # back_button = tk.Button(root, text="Back", command=app.go_back, font=btn_font, width = 18, height= 1)
    # back_button.pack(side="bottom", pady=10)

    root.mainloop()
