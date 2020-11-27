#include <ansi.h> 
#include <room.h>
inherit ROOM; 

#define QINGTIAN    "/u/sanben/special/tianzi/qingtian.c"
#define SPECIAL     "/data/item/special/"


int is_chat_room() 
{ 
        return 1; 
} 

void create()
{       
		object ob;
        set("short", HIY "\n\n                包子工作室" NOR);
        set("long", HIY "\n\n" + TEXT2PIC_D->Display("房间") + "\n\n" NOR
);

        set("exits", ([
                 "gc" : "/d/city/guangchang", 
                   "kd" : "/d/city/kedian",                
                //   "idl" : "/u/idle/workroom",
        ]));
        set("objects", ([
                "/clone/money/coin" : 1,
        ]));

        set("no_fight", 1);
        set("valid_startroom", 1);
        set("sleep_room", 1);
        set("chat_room",1);
        set("valid_startroom", 1);          
        setup();               
                 "/clone/board/sanben_b"->foo();            
        
}

void init()
{

    add_action("do_giveout", "giveout");
    add_action("do_place", "place");
    add_action("do_ip", "ip");
    add_action("do_start", "start");
}

int do_giveout()
{
   object gift, *users;
   int i;

   users = users();
   for(i=0;i<sizeof(users);i++)
   {
       gift = new("/u/sanben/giftpack");       
       gift->move(users[i]);
       tell_object(users[i],HIR"叮~~~天降财神到~~~\n"NOR 
       HIG"恭喜你收到了中华英雄巫师组分发的小礼物包，\n请open giftpack看看你的运气。\n"NOR);   
   }
   return 1;
}

int do_ip()
{
    object *users, gift;
    int i, ii, same, num;
    string *ip_list, ip;

    users = users();


    for( i = 0; i < sizeof(users); i++)
    {
       same = 0;     
       num = sizeof(ip_list); 
       ip = query_ip_number(users[i]);

       if ( num > 0 )
       {
          for(ii=0;ii<num;ii++)
          {
             if ( ip_list[ii] == ip ) same = 1; 
          }
       }
        

       if ( same == 0 )
       {
           gift = new("/u/sanben/giftpack");       
           gift->move(users[i]);

           tell_object(users[i],HIR"叮~~~天降财神到~~~\n"NOR 
           HIG"恭喜你收到了中华英雄巫师组分发的小礼物包，\n请open giftpack看看你的运气。\n"NOR);   
       }      

       if ( ! ip_list )
          ip_list = ({ip});
       else
          ip_list += ({ip});

    }
    return 1;
}

int do_start1()
{
    remove_call_out("count_down");
    call_out("count_down", 5, 5);
    return 1;
}

int do_start()
{
    remove_call_out("do_ip");
    call_out("do_ip", 60);
    message( "story", HIY"【天降财神】天神将在一分种" 
              "后按IP发放礼物，请大家做好准备! \n"NOR, users() );
    return 1;
}


void count_down(int i)
	{	
		

		 message( "story", HIY"【天降财神】天神将在" + chinese_number(i) + 
                        "秒后按IP发放礼物，请大家做好准备! \n"NOR, users() );
		i = i-1;
		if (i > 0 ) 
		{	

			remove_call_out("count_down");
                	call_out("count_down", 1, i);
		}
		else 
		{	message( "story", "\n", users() );
			message( "story", HIG"【天降财神】" + HIY"现在发放礼物!\n"NOR, users() );
			remove_call_out("do_ip");
                	call_out("do_ip", 2, i);
		}
	}



