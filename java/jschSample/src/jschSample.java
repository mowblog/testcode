import java.io.InputStream;
import java.util.Properties;

import com.jcraft.jsch.*;

public class jschSample {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Properties p = new Properties();
//		p.setProperty("cipher.s2c", "aes256-ctr,aes192-ctr,aes128-ctr");
//		p.setProperty("cipher.c2s", "aes256-ctr,aes192-ctr,aes128-ctr");
//		p.setProperty("mac.s2c", "hmac-sha2,hmac-sha1");
//		p.setProperty("mac.c2s", "hmac-sha2,hmac-sha1");
//		p.setProperty("kex", "ecdh-sha2-nistp256");
		p.setProperty("StrictHostKeyChecking", "no");
		
		try {
		JSch jsch=new JSch();
		Session session=jsch.getSession("pi", "192.168.1.7", 22);
		session.setConfig(p);
		session.setPassword("raspberry");
		session.connect();
		Channel channel=session.openChannel("exec");
	    ((ChannelExec)channel).setCommand("pwd");
	    
	    channel.setInputStream(null);
	    InputStream in=channel.getInputStream();

	    channel.connect();

	    byte[] tmp=new byte[1024];
	    while(true){
	    while(in.available()>0){
	      int i=in.read(tmp, 0, 1024);
	      if(i<0)break;
	      System.out.print(new String(tmp, 0, i));
	    }
	    if(channel.isClosed()){
	      if(in.available()>0) continue;
	      System.out.println("exit-status: "+channel.getExitStatus());
	      break;
	    }
	    try{Thread.sleep(1000);}catch(Exception ee){}
	    }
	    channel.disconnect();
	    session.disconnect();
		
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
		
	}

}
