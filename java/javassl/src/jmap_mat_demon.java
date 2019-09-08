class my_passwd {
	private String passwd;
	

	public my_passwd()
	{
		this.passwd = "Changeme_123";
	}
	
	public String get_passwd()
	{
		return this.passwd;
	}
}


public class jmap_mat_demon {

	public static void main(String[] args) {
		my_passwd test = new my_passwd();
		//do something with the password
		test = null;
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
