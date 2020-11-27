
// һ�Ƚ�(1��) ���� ���ӹ� һ�� (���Ը�ָ��id�����������,�ɹ���100%)
// ���Ƚ�(2��) ���� �����һ�� (�ɻ�ȡʮ������һ��)
// ���Ƚ�(3��) ���� �����쾧һ�� (�߼������������)
// ���뽱 (�������вμӳ齱�߾���) ���� ���ڴ����һ�� 

#include <ansi.h>

#define FILE_PATH       "/data/lot/lot_machine.o"
#define CARD            __DIR__"lot_card"
#define FIRST_PRIZE     "/u/sanben/obj/shenyou"
#define SECOND_PRIZE    "/u/sanben/obj/weapon_card"
#define THIRD_PRIZE     "/d/death/obj/tianjing"
#define NORMAL_PRIZE    "/u/sanben/spr_gift"
#define MAX_NUM         300
#define TIME            200702


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
{   
    int num, i;
    object me, ob, *obj;
    string space;	    
	    
    me = this_player();
    ob = this_object();
    space = "";

    if ( ! arg || ( arg != "card" && arg != "lot card") )
       return notify_fail("��Ҫ����ʲô��\n");
       
    if (! present("lot card", me))
       return notify_fail("�Բ�����û�г齱��ѽ��\n");

    if ( me->query("lot_number/" + TIME))
       return notify_fail("�Բ������Ѿ���һ�����˺����ˣ�\n");	

   // if ( me->query("combat_exp") < 500000 )
   //    return notify_fail("�Բ��𣬾���С����ʮ��Ĳ��ܲμӳ齱��\n");		    
	    
			
    restore_object( FILE_PATH, 1 );

    if (ob->query("open_lot") == 1 )	
	return notify_fail("�����Ѿ��������ˣ������ٲμӳ齱�ˣ�\n");
				
    if ( ob->query("number") >= MAX_NUM )
       return notify_fail("�Բ��𣬳齱���Ѿ������ˣ�\n");			

    obj = all_inventory(me);
    for(i=0; i<sizeof(obj); i++) 
    {
	if (base_name(obj[i]) == CARD)
	{
          destruct(obj[i]);
          break;
       }			     
    }	
		
    ob->add("number",1);
    num = ob->query("number");			
    me->set("lot_number/" + TIME, num);	
       	
    ob->set("id_record/" + num, me->query("id"));
    ob->set("name_record/" + num, me->query("name"));

    if ( num < 10 )  space = "       ";    	           
    else 
    if ( num < 100 ) space = "      ";
    else space = "     ";   

   save_object( FILE_PATH,1 );	
			
   message_vision(HIW"$N�ӻ����ó�һ�ų齱���������˻����Ĳ忨���ڡ�\n"NOR, me);

   tell_object(me, "\nֻ���齱������Ļ����ʾ��:\n"+
	     HBRED + HIW"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"+ 
	      "$$                                     $$\n"+
	      "$$" + HIY"  ���ã�����õ����˺�����:"HIG + num + HIY"��" 
                  + space + HIW"$$\n"+
	      "$$                                     $$\n"+
	      "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"NOR);
   return 1;
}



int do_push( string arg )
{	
       int i;
	object me, ob, prize;		
	string name, space1, space2;
		
	me = this_player();
	ob = this_object();
	name = "";
	space1 = "               ";
	space2 = "     ";

       if ( ! arg || (arg != "1" && arg != "2" && arg != "3") )
       {
          tell_object(me, HIR "��ѡpush 1 �� push 2 ��push 3\n" NOR);
          return 1;
       }

	if (! wizardp(me) && time() - me->query_temp("last_push_machine") < 10)
       {
          write("����Ϲ���������û������ϰ��ᰴ���ģ����ǵȻ����!\n");
	   return 1;
       }

       me->set_temp("last_push_machine", time());
       
	restore_object(FILE_PATH, 1);

	message_vision(HIW"ֻ����žડ�һ��" + "$N�����˵�" +
                      chinese_number(atoi(arg)) + "����ť��\n"NOR, me);
		
	if (arg == "1")	
       {
	   for(i=1; i<sizeof(ob->query("name_record"))+1; i++) 
         {								
		name += ob->query("name_record/"+i) + "(" + 
                      ob->query("id_record/"+i) +
			 ")" + "���˺���:" + i + "��|"; 
             if ( i%2 == 0 ) name += "\n";			
         }	
		
	  tell_object(me, HIY"Ŀǰ����"+ ob->query("number") + 
				"�˲μӳ齱:\n"HBGRN HIC+ name +"\n"NOR);			
	  return 1;
	}

	if (arg == "2")
	{	

	    if ( ! ob->query("open_lot") )	
	    { 
              write("���ڻ�û����ѽ��\n");
              return 1;
           }		
	
               if  (ob->query("/prize/"+"1") < 10 ) { space1 += " "; }
		 if  (ob->query("/prize/"+"2") > 9 )  { space2 = "    "; }
		 if  (ob->query("/prize/"+"3") < 10 ) { space2 += " "; }

tell_object(me,
HIG 
"     ����������������������������������������������������\n"+
"     ��  ��������������������������������������������  ��\n"+
"     ��  ��" + MAG"            ��������" + HIG"                  ��  ��\n" +
"     ��  ��              " + HIM HBWHT"һ�Ƚ�"NOR HIG + "                    ��  ��\n" +
"     ��  ��" + space1 + MAG +     ob->query("/prize/"+"1") +
		 "��"HIG + "                    ��  ��\n" +
"     ��  ��                                        ��  ��\n" +
"     ��  ��              "+ HIY HBWHT"���Ƚ�"NOR HIG +"                    ��  ��\n" +
"     ��  ��           "HIY + ob->query("/prize/"+"2") + "��" + space2 +
			ob->query("/prize/"+"3")+"��    "HIG + "             ��  ��\n" +
"     ��  ��                                        ��  ��\n" +
"     ��  ��              "+ HIB HBWHT"���Ƚ�"NOR HIG +"                    ��  ��\n" +
"     ��  ��      "HIB + ob->query("/prize/"+"4") + "��    " +ob->query("/prize/"+"5")+
	"��    " + ob->query("/prize/"+"6") + "��"HIG +"           ��  ��\n" +
"     ��  ��                                        ��  ��\n" +
"     ��  ��   �����������ȡ��Ʒ����������Ч     ��  ��\n" +
"     ��  ��������������������������������������������  ��\n"+
"     ����������������������������������������������������\n"NOR);
		return 1;
			
       }	

	if (arg == "3")
	{				
	   if ( ! ob->query("open_lot") )	
	   { 
             write("���ڻ�û����ѽ��\n");
             return 1;
          }			
			   
	   if( ! me->query("lot_number/" + TIME))
	   {
             write("�ף���û�μӳ齱ѽ��\n");
             return 1;
          }

          message_vision(HIW"�齱�������һ����Ʒ����\n" +
				"$N��ಡ���һ���Ͱѽ�Ʒ�Ž��˶��\n"NOR, me);

 	   if ( me->query("lot_number/" + TIME ) == ob->query("prize/"+ "1"))
	   { 
             prize = new(FIRST_PRIZE); 
             prize->move(me);
	      write(HIG"��ϲ�������һ�Ƚ��������Ѹ�������!\n"NOR);	
             me->delete("lot_number/" + TIME);
             return 1;               
          } 

          if ( me->query("lot_number/" + TIME) == ob->query("prize/"+ "2") 
               || me->query("lot_number/" + TIME) == ob->query("prize/"+ "3"))
	   { 
             prize = new(SECOND_PRIZE); 
             prize->move(me);				    
	      write(HIY"��ϲ������˶��Ƚ��������Ѹ�������!\n"NOR);
             me->delete("lot_number/" + TIME);
             return 1;               	     
          }     

	   if( me->query("lot_number/" + TIME ) == ob->query("prize/"+ "4")
              || me->query("lot_number/" + TIME ) == ob->query("prize/"+ "5")
              || me->query("lot_number/" + TIME ) == ob->query("prize/"+ "6"))
	   { 
              prize = new(THIRD_PRIZE); 
              prize->move(me);
		write(YEL"��ϲ����������Ƚ��������Ѹ�������!\n"NOR);
              me->delete("lot_number/" + TIME);
              return 1;               		
          }
	  
             write("������˹�������ף����ÿ��ģ�\n");
	      prize = new(NORMAL_PRIZE); 
             prize->move(me);	     
             me->delete("lot_number/" + TIME);
             return 1; 
        		       
     }
}

int do_open(string arg)
{    
    object ob;
    int num, i, ii, *prize, same;

    prize = ({});		
    ob = this_object();

    if ( ! arg || arg != "lot" || ! wizardp(this_player()) )
       return 0;			
		
    restore_object(FILE_PATH, 1);			

    if (ob->query("open_lot"))
	 return notify_fail("�Ѿ���������ѽ��\n");
		
    for (i = 0; i < 6; i++)
    {	 
        same = 0;
    	 num = random(query("number"))+ 1;

	 for (ii = 0; ii < i; ii++)
	 {					
	      if ( prize[ii] == num ) { same = 1;}				
	 }
			
	 if (same == 1) {i=i-1;}
	 else   
        {
           ob->set("/prize/"+(i+1), num);
           prize += ({num});
        }
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
	  
		
int do_reset(object me,object ob)
{	
       int i;
		
	me = this_player();
	ob = this_object();

	if ( ! wizardp(me) ) return 0;
          
	ob->delete("name_record");	
	ob->delete("id_record");			     

	ob->delete("open_lot");
	ob->delete("number");

	tell_object(me, HBMAG"�齱�����ݻظ���ʼ״̬��\n"NOR);

	save_object( FILE_PATH, 1 );

	return 1;
		
}

void count_down(int i)
{
       message( "story", HIG"��������Ϣ�����ڳ齱������Ͼ�Ҫ��������������׼��!" +
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
       object ob = this_object();

	restore_object(FILE_PATH,1 );
		
	i = i + 1;
	if ( i == 1 ) 
       {
	   message( "story", HIG"��������Ϣ��" + BLINK HIM"һ�Ƚ���" +
	   ob->query("/prize/"+ i) + "��\n"NOR, users() );
       }
	if ( i == 2 ) 
       {
	   message( "story", HIG"��������Ϣ��"NOR + BLINK YEL"���Ƚ���" +
	   ob->query("/prize/"+ i) + "��   " +
	   ob->query("/prize/"+ (i+1)) + "��\n"NOR, users() );
       }
	if ( i == 3) 
       {
	   message( "story", HIG"��������Ϣ��" + BLINK HIC"���Ƚ���" +
	   ob->query("/prize/"+ (i+1)) + "��  " +
          ob->query("/prize/"+ (i+2)) + "��  " +
	   ob->query("/prize/"+ (i+3)) + "��\n"NOR, users() );
       }

	if (i < 3 ) 
	{	
	   remove_call_out("annouce");
          call_out("announce", 2, i);
	}
	else 
	{  	 
          remove_call_out("ending");
          call_out("ending", 2);
	}

}

void ending()
{	
       string msg;
	message( "vision", HIG"��������Ϣ��" + HIY"�����μ��߾��й���������������Ч��\n" + 			
		  HIG"��������Ϣ��" + HIY"ף����´����֣��������⣡\n"NOR, users() );

       msg = HIG"��������Ϣ�������ʱ�䵽!\n " + YEL"
                     | 
                  \   *  ./ 
                .  * * * . 
               -=*  POP! *=-               
               .  .* * *  . 
                /    *  .\ 
                     |          
     ������/\~~~~~~~~~~~~~\������������^*^���������  $$�� .��  
     ����./��\~~~��~�� ~~~~\ �������´� .���֡� *��   $����$�� *  
     ����/ ^^ \ �T�T�T�T�T�T\.�������� *��*����*��   $���﨎$�� *  
     ��..��[]������� �� |������ .����������*�� $��������$�� *  
     ��&&�������������� ��'|'�� @��������������* $����������$ *  
     �� �����������������������{�z�y�xף���´����֦��||��� \n"NOR; 
             msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL); 
             msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL); 
             msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL); 
             msg = replace_string(msg,"��",NOR HIY"��"NOR YEL); 
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
