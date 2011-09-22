package persistence;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Choice {

	//Params
	int id;
	String content;
	private int questionID;
	private int correct;
	
	//Methods
	public Choice(int id, String content, int choiceQuestion, int choiceCorrect) {
		this.id = id;
		this.content = content;
		this.questionID = choiceQuestion;
		this.correct = choiceCorrect;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}
	
	public boolean save(Connection con) {
		try{
			PreparedStatement st = con.prepareStatement("SELECT COUNT(*) FROM Choice WHERE LOWER(content) = ?");
			st.setString(1, this.content.toLowerCase());
			ResultSet rs = st.executeQuery();
			if(rs.next()){
				if(rs.getInt(1) == 0){
					//Updating Choice table
					st = con.prepareStatement("INSERT INTO Choice VALUES(?,?,?,?)");
					st.setInt(1, this.id);
					st.setString(2, this.content);
					st.setInt(3, this.questionID);
					st.setInt(4, this.correct);
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
		return "ID: " + this.id + "\tCONTENT: " + this.content;
	}
}
