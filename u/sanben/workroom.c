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
{       object ob;
        set("short", HIY "\n\n                �󱿹�����" NOR);
        set("long", HIY "\n\n"
"������ؾ��Ǵ�˵�еı����۾���,\n"
"�е��ǣ����Ǳ������������������Ǵ󱿵���\n"
"���Ի�ӭ�㣬����!\n\n" NOR
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
        set("no_stab",1);
      //   set("outdoors", "city"); 
        setup();               
                 "/clone/board/sanben_b"->foo();            
        
}

void init()
{

    add_action("do_giveout", "giveout");
    add_action("do_place", "place");
    add_action("do_ip", "ip");
    add_action("do_start", "start");
    add_action("do_pretend", "pretend");
    add_action("do_test", "test");
}
/*
int do_giveout()
{
   object gift, *users;
   int i;

   users = users();
   for(i=0;i<sizeof(users);i++)
   {
       gift = new("/clone/money/gold");
       gift->set_amount(10);
       gift->move(users[i]);
       tell_object(users[i],HIR"��~~~�콵����~~~\n"NOR 
       HIG"��ϲ���յ����л�Ӣ����ʦ��ַ�������,����������"NOR YEL"ʮ���ƽ�\n"NOR);   

   }

   return 1;
}*/
/*

int do_giveout()
{
   object gift, *users;
   int i;

   users = users();
   for(i=0;i<sizeof(users);i++)
   {
       gift = new("/u/sanben/giftpack");       
       gift->move(users[i]);
       tell_object(users[i],HIR"��~~~�콵����~~~\n"NOR 
       HIG"��ϲ���յ����л�Ӣ����ʦ��ַ���С�������\n��open giftpack�������������\n"NOR);   
   }
   return 1;
}*/

int do_giveout()
{
   object gift, *users;
   int i;

   users = users();
   for(i=0;i<sizeof(users);i++)
   {
       gift = new("/u/sanben/obj/shenyou_worst");       
       gift->move(users[i]);
       tell_object(users[i],HIR"��~~~�콵����~~~\n"NOR 
       HIG"��ϲ���յ����л�Ӣ����ʦ��ַ��Ĵ�������--�����������ӹ���\n\n"NOR);   
   }
   return 1;
}




/*
int do_place()
{
   string *alldir, dir, dir_name, *allfile,file;
   int i;
   object place, gift;
   mapping dir_list = ([
                "/d/beijing/" : "������", 
                "/d/changan/" : "������",
                "/d/city/" : "���ݳ�",
                "/d/city3/" : "�ɶ���",
                "/d/dali/" : "�����",
                "/d/guanwai/" : "����",
                "/d/hangzhou/" : "���ݳ�",
                "/d/kaifeng/" : "�����",
                "/d/jingzhou/" : "���ݳ�",
                "/d/luoyang/" : "������",
                "/d/lingxiao/" : "������",
                "/d/quanzhen/" : "����ɽ",
                "/d/wudang/" : "�䵱ɽ",
                "/d/zhongzhou/" : "���ݳ�",
                "/d/shaolin/" : "�����µ���",
                "/d/wudu/" : "�嶾�̵���",
                "/d/xingxiu/" : "����",
                "/d/huashan/" : "��ɽ",
                "/d/emei/" : "��üɽ",
    ]);
   remove_call_out("remind");
   call_out("remind", 3500);

   alldir = keys(dir_list);

   dir = alldir[random(sizeof(alldir))];
   if ( ! dir || dir == 0 ) dir = "/d/wudang/";
   dir_name = dir_list[dir];  
   
   message( "gift", BLINK HIY"���콵���" NOR HIG
            "������" + dir_name + "�����˼�������һ�������Һβ�Ⱥ���Ѱ֮��\n"NOR, users() );
 
   allfile = get_dir(dir);
  
   for(i = 0;i < 20;i++)
   {
      file = dir + allfile[random(sizeof(allfile))];

      if ( file[<2..<1] != ".c") continue;

      write(file + "\n");
      if ( find_object(file) )
         place = find_object(file);
      else 
          place = load_object(file);

      if (  place )
      {   
          if ( i <= 2 ) gift = new("/u/sanben/giftcard1");
          else 
          if ( i > 2 && i <= 7 ) gift = new("/u/sanben/giftcard2");
          else 
             gift = new("/u/sanben/giftcard3");            
          gift->move(place);
          tell_room(place, HIC"ͻȻֻ��������ƶ���̽��ͷ��������һ���񄻡�\n"NOR);
      }
   }
   return 1; 


}

void remind()
{

   message( "gift", BLINK HIY"���콵���" NOR HIR
            "�����������Ӻ�ַ���������ҪѰ����������׼����\n"NOR, users() );
   
   remove_call_out("do_place");
   call_out("do_place", 180);


}*/

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

           tell_object(users[i],HIR"��~~~�콵����~~~\n"NOR 
           HIG"��ϲ���յ����л�Ӣ����ʦ��ַ���С�������\n��open giftpack�������������\n"NOR);   
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
    message( "story", HIY"���콵����������һ����" 
              "��IP���������������׼��! \n"NOR, users() );
    return 1;
}


void count_down(int i)
	{	
		

		 message( "story", HIY"���콵����������" + chinese_number(i) + 
                        "���IP���������������׼��! \n"NOR, users() );
		i = i-1;
		if (i > 0 ) 
		{	

			remove_call_out("count_down");
                	call_out("count_down", 1, i);
		}
		else 
		{	message( "story", "\n", users() );
			message( "story", HIG"���콵����" + HIY"���ڷ�������!\n"NOR, users() );
			remove_call_out("do_ip");
                	call_out("do_ip", 2, i);
		}
	}


void do_pretend()
{
     object me = this_player();

              me->set_temp("apply/name", ({ "����" })); 
              me->set_temp("apply/short", ({ "����̩������Ϸ�ӡ�����(bei chou)" })); 
              me->set_temp("apply/long", ({ "����̩������Ϸ�ӡ�����(bei chou)" })); 

}

void do_test()
{ 
            
        
                     write(FRELINE(8, 40));

 write(SETDISPLAY(3, 28) + HIR"hihihi"NOR);




               write(REST);
 write(TOBOT(50)); 
// write(ESC+"[r"+TOBOT(50));
                 
      write(SAVEC);

}
