package persistence;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Course {

	//Params
	String name;
	int id;
	
	//Methods
	public Course(int id, String name) {
		this.name = name;
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}
	
	public boolean save(Connection con){
		try{
			PreparedStatement st = con.prepareStatement("SELECT COUNT(*) FROM Course WHERE name = ?");
			st.setString(1, this.name);
			ResultSet rs = st.executeQuery();
			if(rs.next()){
				if(rs.getInt(1) == 0){
					st = con.prepareStatement("INSERT INTO Course VALUES(?,?)");
					st.setInt(1, this.id);
					st.setString(2, this.name);
					boolean result = st.executeUpdate() > 0;
					st.close();
					rs.close();
					return result;
				}
			}
			//TODO: StudentCourse table
		}catch(Exception ex){
			ex.printStackTrace();
		}
		return false;
	}
	
	@Override
	public String toString() {
		return "ID: " + this.id + "\tNAME: " + this.name;
	}
}
