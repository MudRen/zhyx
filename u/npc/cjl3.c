// by yuchang
inherit ROOM;
#include <ansi.h>
#include <room.h>
int do_press(string arg);
void init();


void create()
{
      set("short", "²Ø½£Â®");
      set("long",
"[1;32mÕâÀï¾ÍÊÇ°Á½£É½×¯µÄ²Ø½£Â®\n"
"ÔÚ³¡ÖÐ¼äÓÐÒ»¿é¾Þ´óµÄºìÄ¾ÖÆÎäÆ÷¼Ü(shelf)\n"
);
   set("exits",([
           "south" : __DIR__"square",
]));


  set("item_desc", ([
     "shelf" : "ÕâÊÇÒ»Ö»ÓÉÃû¹óºìÄ¾ËùÖÆ£¬ÓÃÀ´´æ·ÅÅä½£µÄ¼Ü×Ó,ËÆºõ¿ÉÒÔÄÃ³öÀ´(take sword)¡£\n",

  ]));
  set("aocangtian", 1);

  setup();
}

void init()
{
        add_action("do_press", "press");
      add_action("do_take", "take");
      add_action("do_quit","kill");
      add_action("do_steal","steal");
}
int do_press(string arg)
{
    string p;
            object me,obj;
             object ob;
             me = this_player();
              ob = this_object();
    p = sprintf("%d", this_player()->query("_passwd")); 
    if( !arg || arg == "" )
    {
        write("±ðÏ¹°´£¡\n");
        return 1;
    }
    if( arg == p )
    {
        message_vision("Ö»ÌýµÃÒ»ÕóÂ¡Â¡µÄÏìÉùÓÉÔ¶¼°½ü¡£\n", this_player());
        message_vision("½£Â¯»º»ºÒÆÁË¿ªÀ´£¬Â¶³öÒ»¸ö¶´¡£Ò»°Ñ±¦½£³ÊÏÖÔÚÄãÃæÇ°¡£\n", this_player());
            obj = new ("/d/zhuanshi/obj/jiushi");
            obj->move(me);
             return 1;
      }
    else
    {
            message_vision("$NÒ»ÕóÂÒ°´£¬Í»È»Ê¯°åµÄ·ìÏ¶¼äÉä³öÒ»Ö§¶¾¼ý£¡¡£\n", this_player());
            this_player()->die();
            return 1;
        }
}

int do_steal(string arg)
{
        write(this_player()->query("name")+"£¬²»ÒªÎª´Ë²»²ÅÖ®ÊÂ£¡\n");
        return 1;
}

int do_take(string arg)
{
       object me,obj;
        object ob;
       me = this_player();

        ob = this_object();
       if( !arg || arg!="sword" ) return notify_fail("ÄãÒªÄÃÊ²Ã´£¿\n");
          if (me->query("najian")) {
       tell_object(me,CYN "ÀË·­ÔÆµÄÉíÓ°Í»È»³öÏÖÔÚÒ»ÕóÑÌÎíÖ®ÖÐ¡£\n\n");
       tell_object(me,HIR "ÀË·­ÔÆÒ»°ÍÕÆÇÃÔÚÄãÊÖÉÏ£ºÐ¡ÅóÓÑ£¬²»ÒªÂÒ¶¯£¡\n\n");
       tell_object(me,CYN "Ö»¼ûÒ»ÕóÑÌÎí¹ýáá£¬ÀË·­ÔÆµÄÉíÓ°ÒÑ¾­²»¼ûÁË¡£\n" NOR);
       return 1;

}
      obj = new ("/d/ajszhuang/npc/obj/ling");
       obj->move(me);

       // mark the owner who take it
       obj->set("owner", me->query("id"));

       message_vision(HIC"$N²»¾õµÃ´ôÁËÒ»´ô£¬ÀïÃæ¾ÓÈ»ÓÐ100Óà°Ñ±¦½££¬µ½µ×ÊÇÄÄÒ»°ÑÄØ£¿\n"
             "Í»È»ÄãÌýµ½£ºÅ¾¡°µÄÒ»Éù£¬Ê²Ã´¶«Î÷µôÔÚÄã»³Àï¡£\n" NOR, this_player());
       me->delete("najian");
       me->set("najian",1);
       me->start_busy(2);
       return 1;
}



