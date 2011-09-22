package persistence;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Questionaire {

	//Params
	int id;
	String name;
	int course;
	int student;
	
	//Methods
	public Questionaire(int id, String name, int course, int student) {
		super();
		this.id = id;
		this.name = name;
		this.course = course;
		this.student = student;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getCourse() {
		return course;
	}

	public void setCourse(int course) {
		this.course = course;
	}

	public int getStudent() {
		return student;
	}

	public void setStudent(int student) {
		this.student = student;
	}
	
	public boolean save(Connection con){
		try{
			PreparedStatement st = con.prepareStatement("INSERT INTO Questionaire VALUES(?,?,?,?)");
			st.setInt(1, this.id);
			st.setString(2, this.name);
			st.setInt(3, this.course);
			st.setInt(4, this.student);
			boolean result = st.executeUpdate() > 0;
			st.close();
			return result;
		}catch(Exception ex){
			ex.printStackTrace();
		}
		return false;
	}
	
	@Override
	public String toString() {
		return "ID: " + this.id + "\tNAME: " + this.name + "\tCOURSE: " + this.course + "\tSTUDENT: " + this.student;
	}
	
}
