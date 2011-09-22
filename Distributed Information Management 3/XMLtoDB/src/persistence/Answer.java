package persistence;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Answer {

	//Params
	int id;
	int student;
	int questionaire;
	int question;
	int choice;
	
	
	//Method
	public Answer(int id, int student, int questionaire, int question, int choice) {
		super();
		this.id = id;
		this.student = student;
		this.questionaire = questionaire;
		this.question = question;
		this.choice = choice;
	}


	public int getId() {
		return id;
	}


	public void setId(int id) {
		this.id = id;
	}


	public int getStudent() {
		return student;
	}


	public void setStudent(int student) {
		this.student = student;
	}


	public int getQuestionaire() {
		return questionaire;
	}


	public void setQuestionaire(int questionaire) {
		this.questionaire = questionaire;
	}


	public int getQuestion() {
		return question;
	}


	public void setQuestion(int question) {
		this.question = question;
	}
	
	public int getChoice() {
		return choice;
	}


	public void setChoice(int choice) {
		this.choice = choice;
	}


	public boolean save(Connection con){
		try{
			PreparedStatement st = con.prepareStatement("SELECT COUNT(*) FROM Answer WHERE Student_id = ? AND Questionaire_id = ? AND Question_id = ? AND Choice_id = ?");
			st.setInt(1, this.student);
			st.setInt(2, this.questionaire);
			st.setInt(3, this.question);
			st.setInt(4, this.choice);
			ResultSet rs = st.executeQuery();
			if(rs.next()){
				if(rs.getInt(1) == 0){
					st = con.prepareStatement("INSERT INTO Answer (`Student_id`,`Questionaire_id`,`Question_id`,`Choice_id`) VALUES(?,?,?,?)");
					st.setInt(1, this.student);
					st.setInt(2, this.questionaire);
					st.setInt(3, this.question);
					st.setInt(4, this.choice);
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
		return "ID: " + this.id + "\tSTUDENT: " + this.student + "\tQUESTIONAIRE: " + this.questionaire + "\t\tQUESTION: " + this.question + "\tCHOICE: " + this.choice;
	}
}
