package FIS.Entity;

import java.io.Serializable;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
@XmlRootElement(name = "person") 
public class SerializerEntity  implements Serializable{
	   
	public enum Gender{ male,female;}
	
	private String name;  
	 
	
    private Integer age ;  
 
	
    private Gender gender;  

    @XmlElement(name = "name") 
    public String getName() {  
        return name;  
    }  
 
    public void setName(String name) {  
        this.name = name;  
    }  
    @XmlElement(name = "age") 
    public Integer getAge() {  
        return age;  
    }  
 
    public void setAge(Integer age) {  
        this.age = age;  
    }  
    @XmlElement(name = "gender") 
    public Gender getGender() {  
        return gender;  
    }  
 
    public void setGender(Gender gender) {  
        this.gender = gender;  
    }
}

