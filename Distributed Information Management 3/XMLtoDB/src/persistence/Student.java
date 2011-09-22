package persistence;

import java.sql.*;

public class Student {
	
	//Parameters
	int id;
	String name;
	String surname;
	String matriculationID;
	String password;
	
	//Methods
	public Student(int id, String name, String surname, String matriculationID,
			String password) {
		super();
		this.id = id;
		this.name = name;
		this.surname = surname;
		this.matriculationID = matriculationID;
		this.password = password;
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

	public String getSurname() {
		return surname;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}

	public String getMatriculationID() {
		return matriculationID;
	}

	public void setMatriculationID(String matriculationID) {
		this.matriculationID = matriculationID;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}
	
	public boolean save(Connection con){
		try{
			PreparedStatement st = con.prepareStatement("SELECT COUNT(*) FROM Student WHERE matriculationNumber = ?");
			st.setString(1, this.matriculationID);
			ResultSet rs = st.executeQuery();
			
			if(rs.next()){
				if(rs.getInt(1) == 0){
					st = con.prepareStatement("INSERT INTO Student VALUES(?,?,?,?,?)");
					st.setInt(1, this.id);
					st.setString(2, this.name);
					st.setString(3, this.surname);
					st.setString(4, this.matriculationID);
					st.setString(5, this.password);
					boolean result = st.executeUpdate() > 0;
					st.close();
					rs.close();
					return result;
				}
			}
		}catch(Exception ex){
			ex.printStackTrace();
		}
		return false;
	}
	
	@Override
	public String toString() {
		return "ID: " + this.id + "\tNAME: " + this.name + "\tSURNAME: " + this.surname;
	}

}
