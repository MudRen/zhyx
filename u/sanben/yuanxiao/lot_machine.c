
// һ�Ƚ�(1��) ���� ����쾧   һ��
// ���Ƚ�(2��) ���� ����ɿ��� һ�� (ָ��һ���츳��һ)
// ���Ƚ�(3��) ���� �����޻��� һ�� (ָ��һ���츳�Ե�ʧ������һ)
// ������ (�������вμӳ齱�߾���) ���� ��Բ һ��

#include <ansi.h>

#define FILE_PATH       __DIR__"lot_machine.o"
#define CARD            __DIR__"lot_card"
#define FIRST_PRIZE     "/d/death/obj/tianjing"
#define SECOND_PRIZE    __DIR__"tianfu"
#define THIRD_PRIZE     __DIR__"fig"
#define NORMAL_PRIZE    __DIR__"dumpling"


inherit ITEM;

void create()
{
        set_name(HIG "�齱��" NOR, ({ "lot machine", "lot", "machine"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG 
"     ����������������������������������������������������\n"+
"     ��  ��������������������������������������������  ��\n"+
"     ��  ��           ��ӭ�μӳ齱�             ��  ��\n" +
"     ��  ��             �忨��  |===|              ��  ��\n" +
"     ��  ��             (insert card)              ��  ��\n" +
"     ��  ��                                        ��  ��\n" +
"     ��  ��      @            @          @         ��  ��\n" +
"     ��  ��    @ 1 @        @ 2 @      @ 3 @       ��  ��\n" +
"     ��  ��      @            @          @         ��  ��\n" +
"     ��  ��  ��ѯ�μ���   ��ѯ����   �콱        ��  ��\n" +
"     ��  ��          (push 1 or 2 or 3)            ��  ��\n" +
"     ��  ��                                        ��  ��\n" +
"     ��  ��������������������������������������������  ��\n"+
"     ����������������������������������������������������\n"NOR);
                set("unit", "̨");
                set("value", 10000);
                set("weight", 3000);
                set("material", "wood");
		  set("no_get",1);
		  set("no_drop",1);		  		  
             }	         
        setup();
}

void init()
	{
		add_action("do_insert","insert");
		add_action("do_push","push");
		add_action("do_open","open");
		add_action("do_reset","reset");
	}
		
int do_insert( string arg )

	{   int num, i;
	    object me, ob, *obj;
	    string space;	    
	    
	    me = this_player();
	    ob = this_object();
	    space = "";
	
	    if ( arg == "card" || arg == "lot card")
		{   
		    if (! present("lot card", me))
		    return notify_fail("�Բ�������û���õ��齱��ѽ��\n");

		    if ( me->query("lot_number") > 0 )
		    return notify_fail("�Բ������Ѿ���һ�����˺����ˣ�\n");
		    
			
		    restore_object( FILE_PATH, 1 );
	   	    if (this_object()->query("open_lot") == 1 )	
	    	    return notify_fail("�����Ѿ��������ˣ������ٲμӳ齱�ˣ�\n");
				
		    if ( ob->query("number") > 39 )
		    return notify_fail("�Բ��𣬳齱���Ѿ������ˣ�\n");
			

			obj = all_inventory(this_player());
			for(i=0; i<sizeof(obj); i++) 
			    {
				if (base_name(obj[i]) == CARD)
					{destruct(obj[i]);break;}
			     }	
		
			ob->add("number",1);
			num = ob->query("number");			
			me->set("lot_number", num);
			
			ob->set("/id_record/" + num, me->query("id"));
			ob->set("/name_record/" + num, me->query("name"));

			if ( num < 10 ) {space = "       ";}
			           else {space = "      ";}

			save_object( FILE_PATH,1 );	
			
		    message_vision(HIW"$N�ӻ����ó�һ�ų齱���������˻����Ĳ忨���ڡ�\n"NOR, this_player());
		    tell_object(me, "\nֻ���齱������Ļ����ʾ��:\n"+
			HBRED + HIW"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"+ 
			 "$$                                     $$\n"+
			 "$$" + HIY"  ���ã�����õ����˺�����:"HIG + num + HIY"��" + space + HIW"$$\n"+
			 "$$                                     $$\n"+
			 "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"NOR);
			return 1;
		}
		else {return notify_fail("��Ҫ����ʲô��\n");}
	}



int do_push( string arg )

	{	int i;
		object me, ob, prize;		
		string name, space1, space2;
		
		me = this_player();
		ob = this_object();
		name = "";
		space1 = "               ";
		space2 = "     ";
		if (! wizardp(me) && time() - me->query_temp("last_push_machine") < 60)
		    {write("��������ѽ��磬����Ϲ���������û������ϰ��ᰴ����!\n");
	    	     return 1;}

		    me->set_temp("last_push_machine", time());
		
		if (arg == "1")	{
		restore_object(FILE_PATH, 1);
		message_vision(HIW"ֻ����žડ�һ��" + "$N�����˵�һ����ť��\n"NOR, me);

		for(i=1; i<sizeof(ob->query("name_record"))+1; i++) 
			    {								
				name += ob->query("/name_record/"+i) + "(" + ob->query("/id_record/"+i) +
				 ")" + "         ���˺���: " + i + "��\n"; 				
			     }			
		
		tell_object(me, HIY"Ŀǰ����"+ ob->query("number") + 
				"�˲μӳ齱:\n"HBGRN HIC+ name +"\n"NOR);
			
			return 1;
		  }
		if (arg == "2")
		  {	
			restore_object(FILE_PATH, 1);
			message_vision(HIW"ֻ����žડ�һ��" + "$N�����˵ڶ�����ť��\n"NOR, me);

			if (this_object()->query("open_lot") == 0 )	
			{ write("���ڻ�û����ѽ��\n");return 1;}		
			else
			{	if  (ob->query("/prize/"+"1") < 10 ) {space1 += " ";}
				if  (ob->query("/prize/"+"2") > 9 ) {space2 = "    ";}
				if  (ob->query("/prize/"+"3") < 10 ) {space2 += " ";}
tell_object(me,
HIG 
"     ����������������������������������������������������\n"+
"     ��  ��������������������������������������������  ��\n"+
"     ��  ��" + MAG"            ��������" + HIG"                  ��  ��\n" +
"     ��  ��              " + HIM HBWHT"һ�Ƚ�"NOR HIG + "                    ��  ��\n" +
"     ��  ��" + space1 + MAG +     ob->query("/prize/"+"1") +
		 "��"HIG + "                     ��  ��\n" +
"     ��  ��                                        ��  ��\n" +
"     ��  ��              "+ HIY HBWHT"���Ƚ�"NOR HIG +"                    ��  ��\n" +
"     ��  ��           "HIY + ob->query("/prize/"+"2") + "��" + space2 +
			ob->query("/prize/"+"3")+"��    "HIG + "             ��  ��\n" +
"     ��  ��                                        ��  ��\n" +
"     ��  ��              "+ HIB HBWHT"���Ƚ�"NOR HIG +"                    ��  ��\n" +
"     ��  ��      "HIB + ob->query("/prize/"+"4") + "��      " +ob->query("/prize/"+"5")+
	"��	  " + ob->query("/prize/"+"6") + "��"HIG +"   	   ��  ��\n" +
"     ��  ��                                        ��  ��\n" +
"     ��  ��   �����������ȡ��Ʒ����������Ч     ��  ��\n" +
"     ��  ��������������������������������������������  ��\n"+
"     ����������������������������������������������������\n"NOR);
			return 1;
			}			
		  }	

		if (arg == "3")
		  {				
			restore_object(FILE_PATH, 1);
			message_vision(HIW"ֻ����žડ�һ��" + "$N�����˵�������ť��\n"NOR, me);			
			if (ob->query("open_lot") == 0 )	
			{ write("���ڻ�û����ѽ��\n");return 1;}			
			   
			    if(me->query("lot_number") == 0)
			    {write("�ף���û�μӳ齱ѽ��\n");return 1;}

				   message_vision(HIW"�齱�������һ����Ʒ����\n" +
					"$N��ಡ���һ���Ͱѽ�Ʒ�Ž��˶��\n"NOR, me);

 	   			   if(me->query("lot_number") == ob->query("/prize/"+ "1"))
				   { prize = new(FIRST_PRIZE); prize->move(me);
					write(HIG"��ϲ�������һ�Ƚ��������Ѹ�������!\n"NOR);
					me->delete("lot_number");return 1;}

				   if(me->query("lot_number") == ob->query("/prize/"+ "2"))
				   { prize = new(SECOND_PRIZE); prize->move(me);				    
					write(HIY"��ϲ������˶��Ƚ��������Ѹ�������!\n"NOR);
					me->delete("lot_number");return 1;}

				    if(me->query("lot_number") == ob->query("/prize/"+ "3"))
				   { prize = new(SECOND_PRIZE); prize->move(me);				     
					write(HIY"��ϲ������˶��Ƚ��������Ѹ�������!\n"NOR);
					me->delete("lot_number");return 1;}

				    if(me->query("lot_number") == ob->query("/prize/"+ "4"))
				   { prize = new(THIRD_PRIZE); prize->move(me);
					write(YEL"��ϲ����������Ƚ��������Ѹ�������!\n"NOR);
					me->delete("lot_number");return 1;}

				     if(me->query("lot_number") == ob->query("/prize/"+ "5"))
				   { prize = new(THIRD_PRIZE); prize->move(me);
					write(YEL"��ϲ����������Ƚ��������Ѹ�������!\n"NOR);
					me->delete("lot_number");return 1;}
				
				     if(me->query("lot_number") == ob->query("/prize/"+ "6"))
				   { prize = new(THIRD_PRIZE); prize->move(me);
					write(YEL"��ϲ����������Ƚ��������Ѹ�������!\n"NOR);
					me->delete("lot_number");return 1;}

				   else {write("������˹�����������Ԫ����Բһ����лл������Ϸ��\n");
					  prize = new(NORMAL_PRIZE); prize->move(me);
					  me->delete("lot_number");
					  return 1;}
		       
		    }
		else 
		  {   
			tell_object(me, HIR "��ѡpush 1 �� push 2 ��push 3\n" NOR);
			return 1;  
		   }	
	}

int do_open(string arg)
	{
	    if (arg == "lot")
	    {	
		object ob;
		int num, i, ii, *prize, same;
		prize = ({});
		
		ob = this_object();

		if (! wizardp(this_player()))
		return notify_fail("�Բ�����������ʦ����Ȩ������\n");		
		
		restore_object(FILE_PATH, 1);			

		if (ob->query("open_lot") == 1)
		return notify_fail("�Ѿ���������ѽ��\n");
		
		for (i = 0; i < 6; i++)
		{	same = 0;
    			num = random(40)+ 1;

			for (ii = 0; ii < i; ii++)
			{					
				if ( prize[ii] == num )
				{ same = 1;}				
			}
			
			if (same == 1) 
				{i=i-1;}
			else   {ob->set("/prize/"+(i+1), num);prize += ({num});}
		}				
			ob->set("open_lot",1);
			save_object(FILE_PATH, 1);			
			 i = 10;
			 message( "story", HIC"��������Ϣ��Ϲ����[Sanben]: ͬ־�Ǻã����׼��������������\n" +
						 "��������Ϣ��Ϲ����[Sanben]: ���ڰ�������ҿ����!\n" NOR, users() );
               	remove_call_out("count_down");
                	call_out("count_down", 5, i);			
			return 1;	
					
	    }		     
	     else
		 return 0;		
	}
		
int do_reset(object me,object ob)

	{	int i;
		
		me = this_player();
		ob = this_object();

		if (wizardp(me))

		    {  restore_object(FILE_PATH, 1);
			
			for (i = 1; i < 41; i++)
			    {	
				ob->delete("/name_record/"+ i);	
				ob->delete("/id_record/"+ i);				
			     }

			ob->set("open_lot", 0);
			ob->set("number", 0);

			tell_object(me, HBMAG"�齱�����ݻظ���ʼ״̬��\n"NOR);
			save_object( FILE_PATH, 1 );
			return 1;
		    }
		else
		    return 0;			
	}

void count_down(int i)
	{	
		

		 message( "story", HIG"��������Ϣ��ʥ���齱������Ͼ�Ҫ��������������׼��!" +
			chinese_number(i) + "�뵹��ʱ��ʼ......\n"NOR, users() );
		i = i-1;
		if (i > 0 ) 
		{	

			remove_call_out("count_down");
                	call_out("count_down", 1, i);
		}
		else 
		{	message( "story", "\n", users() );
			message( "story", HIG"��������Ϣ��" + HIY"���ڹ���������!\n"NOR, users() );
			remove_call_out("announce");
                	call_out("announce", 2, i);
		}
	}

void announce(int i)
	{	
		restore_object(FILE_PATH,1 );
		
		i = i + 1;
		if ( i == 1 ) {
		message( "story", HIG"��������Ϣ��" + BLINK HIM"һ�Ƚ���" +
		this_object()->query("/prize/"+ i) + "��\n"NOR, users() );}
		if ( i == 2 ) {
		message( "story", HIG"��������Ϣ��"NOR + BLINK YEL"���Ƚ���" +
		this_object()->query("/prize/"+ i) + "��   " +
		this_object()->query("/prize/"+ (i+1)) + "��\n"NOR, users() );}
		if ( i == 3) {
		message( "story", HIG"��������Ϣ��" + BLINK HIC"���Ƚ���" +
		this_object()->query("/prize/"+ (i+1)) + "��  " +
		this_object()->query("/prize/"+ (i+2)) + "��  " +
		this_object()->query("/prize/"+ (i+3)) + "��\n"NOR, users() );}


		if (i < 3 ) 
		{	
			remove_call_out("annouce");
                	call_out("announce", 2, i);
		}
		else 
		{  	 remove_call_out("ending");
                	 call_out("ending", 2);
		}

	}

void ending()
	{	string msg;
		message( "vision", HIG"��������Ϣ��" + HIY"�����μ��߾��й���������������ȡ��\n" + 			
			HIG"��������Ϣ��" + HIY"ף��Ҷȹ�һ������ʥ��֮ҹ��\n"NOR, users() );
msg = HIG"��������Ϣ�������ʱ�䵽!\n " + YEL"
                     | 
                  \   *  ./ 
                .  * * * . 
               -=*  POP! *=-               
               .  .* * *  . 
                /    *  .\ 
                     |          
     ������/\~~~~~~~~~~~~~\������������^*^���������  $$�� .��  
     ����./��\~~~��~�� ~~~~\ ������ʥ�� .���֡� *��   $����$�� *  
     ����/ ^^ \ �T�T�T�T�T�T\.�������� *��*����*��   $���﨎$�� *  
     ��..��[]������� �� |������ .����������*�� $��������$�� *  
     ��&&�������������� ��'|'�� @��������������* $����������$ *  
     �� �����������������������{�z�y�xף��ʥ�����֦��||��� \n"NOR; 
             msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL); 
             msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL); 
             msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL); 
             msg = replace_string(msg,"ʥ",NOR HIY"ʥ"NOR YEL); 
             msg = replace_string(msg,"��",NOR HIY"��"NOR YEL); 
             msg = replace_string(msg,"��",NOR HIY"��"NOR YEL); 
             msg = replace_string(msg,"��",NOR HIY"��"NOR YEL); 
             msg = replace_string(msg,"��",NOR HIG"��"NOR YEL); 
             msg = replace_string(msg,"��",NOR HIG"��"NOR YEL); 
	      msg = replace_string(msg,"��",NOR HIR"��"NOR YEL); 
	      msg = replace_string(msg,"��",NOR HIG"��"NOR YEL); 
	      msg = replace_string(msg,"��",NOR HIR"��"NOR YEL); 
	      msg = replace_string(msg,"��",NOR BLINK HIY"��"NOR YEL); 
	      msg = replace_string(msg,"HIG",HIG); 
	      msg = replace_string(msg,"HIC",HIC); 
	      msg = replace_string(msg,"HIY",HIY); 		
	message("vision",msg,users() ); 
	}
