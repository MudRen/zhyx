#include <ansi.h>
inherit F_SSERVER; 

mapping exits_name=([
"east":            "����",
"south":           "�Ϸ�",
"west":            "����",
"north":           "����",
"eastup":          "���Ϸ�",
"southup":         "���Ϸ�",
"westup":          "���Ϸ�",
"northup":         "���Ϸ�",
"eastdown":        "���·�",
"southdown":       "���·�",
"westdown":        "���·�",
"northdown":       "���·�",
"northeast":       "������",
"northwest":       "������",
"southeast":       "���Ϸ�",
"southwest":       "���Ϸ�",
"up":              "�Ϸ�",
"southeast":       "���Ϸ�",
"southwest":       "���Ϸ�",
"up":              "�Ϸ�",
"down":            "�·�",
"enter":           "���",
"out":             "���",
]);
int do_she(string arg,object me,object bow,int num);
int do_shoot(string id,object me,object room,string what,int m,object bow,int num);

string exits_reverse(string dir);

string exits_reverse(string dir)
{
 if( dir=="east" ) return "west";
 if( dir=="west" ) return "east";
 if( dir=="south" ) return "north";
 if( dir=="north" ) return "south";
 if( dir=="eastup" ) return "westdown";
 if( dir=="westup" ) return "eastdown";
 if( dir=="southup" ) return "northdown";
 if( dir=="northup" ) return "southdown";
 if( dir=="eastdown" ) return "westup";
 if( dir=="westdown" ) return "eastup";
 if( dir=="southdown" ) return "northup";
 if( dir=="northdown" ) return "southup";
 if( dir=="northeast" ) return "southwest";
 if( dir=="northwest" ) return "southeast";
 if( dir=="southwest" ) return "northeast";
 if( dir=="southeast" ) return "northwest";
 if( dir=="up" ) return "down";
 if( dir=="down" ) return "up";
 if( dir=="enter" ) return "out";
 if( dir=="out" ) return "enter";

 return "";
}

int perform(object me,object target)
{
  object bow;
  int num;

  if( !objectp(bow=me->query_temp("weapon"))
      || !bow->query("is_bow") )
  return notify_fail("����û�����أ������������������\n");

  num=me->query_skill("lianzhu-arrow",1)/100+1;

  if( num < 2 || me->query_skill("arrow",1) < 100 )
  return notify_fail("���Ǻú�������ļ����ɣ�\n");

  message_vision(HIY"$N�Ӽ����ڳ��"HIW+CHINESE_D->chinese_number(num)+HIY"֧"HIW"���"HIY"������"
       +bow->query("name")+HIY"�ϣ�׼��ʩչ��ƽ��������"
       +HIR"�������"+HIY"����\n"NOR,me);
  input_to("do_she",me,bow,num);
  return 1;
}


int do_she(string arg,object me,object bow,int num)
{
   object ob,room;
   int i,n,m;
   string what;
   mapping exits;

   room=environment(me);
   if( environment(me)->query("no_fight") )
   {
    tell_object(me,"���ﲻ��ս����\n");
    return 1;
   }

   if( bow->query("duration")<0 )
   {
    message_vision("$N���е�"+bow->query("name")+"���ԡ���һ�����ˣ�\n",me);
    destruct(bow);
    return 1;
   }

   if( me->query_str() < bow->query("dam")/20 )
   {
    tell_object(me,"��ʹ�����̵�����Ҳ��������������������������\n");  
    return 1;
   }

   if( me->is_busy() )
   {
    tell_object(me,"��������æ���أ�\n");
    return 1;
   }

   if( me->query("qi") < 400*num || me->query("jing") < 100*num )
   {
    tell_object(me,"�����ھ���������ӯ�������������ʩչ��������\n"); 
    return 1;
   }

   if( sscanf(arg,"she %s %d",what,n)==2 )
   {
    if( n > bow->query("dam")/200 ) n=bow->query("dam")/200;
    for(i=0;i<n;i++)
    {
      if( room && mapp(exits=room->query("exits")) && stringp(exits[what]) )
      {
       m=i+1;
       room=find_object(exits[what]);
      }
    }

    if( room==environment(me) )
    {
     tell_object(me,"������㣬��������ѽ�㣿\n");
     return 1;
    }

    if( room)
     {
      if( room->query("have_quest") )
      { 
       tell_object(me,"�������������ӣ����������Ҳ��\n"); 
       return 1;
      }

      "/cmds/std/look.c"->look_room(me,room);  
      message_vision(HIY"���ֻ��$N����һ�������Ϲ�ʽ����"HIR
       +exits_name[what]+HIY"�ѹ�����.......\n"NOR,me);
      tell_object(all_inventory(room),HIB"�����һ�����ҵ�ɱ����"HIR
       +exits_name[exits_reverse(what)]+HIB"��������\n"NOR);

      tell_object(me,HIR+exits_name[what]+HIW"���龰��һĿ��Ȼ��"
                                      +"�������������׼�ˡ���>\n"NOR);   
      me->start_busy(3+random(3));  
      input_to("do_shoot",me,room,what,m,bow,num);
     } else
      tell_object(me,"������㣬��������ѽ�㣿\n");  

    } else
      tell_object(me,"������������˼ҽ̽���ɣ�\n");
    return 1;
}

int do_shoot(string arg,object me,object room,string what,int m,object bow,int num)
{
  int k;

  for(k=0;k<num;k++)
  bow->do_shoot(arg,me,bow,room,what,m);
  if( num>3 ) num=3;
  me->start_busy(num*2);
  return 1;
} 

