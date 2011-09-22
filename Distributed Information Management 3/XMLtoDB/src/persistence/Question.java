package persistence;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;


public class Question {

	//Params
	String content;
	int id;
	String questionaire;

	//Methods
	public Question(String content, int id, String questionaire) {
		this.content = content;
		this.id = id;
		this.questionaire = questionaire;
	}

	public String getContent() {
		return content;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public void setContent(String content) {
		this.content = content;
	}
	
	public String getQuestionaire() {
		return questionaire;
	}

	public void setQuestionaire(String questionaire) {
		this.questionaire = questionaire;
	}

	public boolean save(Connection con) {
		try{
			PreparedStatement st = con.prepareStatement("SELECT COUNT(*) FROM Question WHERE LOWER(content) = ?");
			st.setString(1, this.content.toLowerCase());
			ResultSet rs = st.executeQuery();
			if(rs.next()){
				if(rs.getInt(1) == 0){
					//Updating Question table
					st = con.prepareStatement("INSERT INTO Question(`content`) VALUES(?)");
					st.setString(1, this.content);
					boolean result = st.executeUpdate() > 0;
					
					//Updating QuestionaireQuestion table
					String regex = "[0-9]+[,[0-9]+]*";
					if(this.questionaire.matches(regex)){
						String questionairesIDS[] = this.questionaire.split(",");
						for(int i=0;i<questionairesIDS.length;i++){
							st = con.prepareStatement("INSERT INTO QuestionaireQuestion VALUE(?,?)");
							st.setInt(1, Integer.parseInt(questionairesIDS[i]));
							st.setInt(2, this.id);
							st.executeUpdate();
						}
					}else{
						st = con.prepareStatement("INSERT INTO QuestionaireQuestion VALUE(?,?)");
						st.setInt(1, Integer.parseInt(this.questionaire));
						st.setInt(2, this.id);
						st.executeUpdate();
					}
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
