#include <ansi.h>
inherit ROOM;

       void create() 
       { 
                   set("short", HIY "\n\n�� �� �� �� �� ��" NOR);
                   set("long", HIG "�������л���Ա�������ģ�ֻ������"
                               "���ܿ�����������Զ��\n����ذڷ��źܶ�"
                               "�Զ��ۻ���(ASM)��\n" NOR
                   );
                   set("exits", ([
                          "west"  :  "/u/yuchang/center/dating",
                   ]));

                   set("no_fight", 1); 
                   set("item_desc", ([ 
                          "asm"  :    "������Ļ����ʾ��" HIM + BLINK" �����(insert)��Ļ�Ա�� " NOR 
                                      "��������������\n�����Ÿ�����ֵİ�Ť��\n",
                   ]));

                   setup();     
       } 


void init()
{
        add_action("do_insert", "insert");
        add_action("do_pull", "pull");
        add_action("do_list", "list");
        add_action("do_buy", "want");
        
}
int do_insert(string arg)
{
        object me, ob;
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "card" || arg == "zhyx card")
        {
                if (! ob = present("zhyx card", me)) return 0;

                if (me->query("temp/insert"))
                        return notify_fail("����ûȡ��!\n");

                if (me->is_busy())
                {
                        return notify_fail("����æ���ء�\n");
                        return 1; 
                }
                destruct(ob);
                write(HIW "�㽫��Ƭ�����Զ��ۻ���...\n" NOR);
                write(HIY "�л��Զ��ۻ������ڶ�ȡ�㿨�ϵ����ݣ����Ժ�...\n" NOR);
                me->set("temp/insert", 1);
                call_out("show", 4 + random(2));
                return 1;
        }
}

//���ݶ�ȡ��ϣ���������
int show()
{  
   int rmb;
   object me = this_player();
   rmb = this_player()->query("rmb");
   tell_object(me, HIC "��Ŀǰ�Ĵ��Ϊ" + chinese_number(rmb) + "Բ����ҡ�\n" NOR);
   write(HIG "���ݶ�ȡ�ɹ���������(list)��ʾ���Թ������Ʒ������(want)������Ʒ��\n" NOR);
   this_player()->set("temp/can_pull", 1);
     
   return 1; 
}

int do_list()
{
   string msg;
   if (! this_player()->query("temp/insert"))
   {
           write("���Ȳ����Ա����\n");
           return 1;
   }
  msg = HIC "�����ơ�                           \t�����á�            ���ɹ��ʡ�                ���۸�\n\n" NOR;
  msg +=HIG "��������(zhenming tianzi)              ������������            100%                   ��1000.00\n";
  msg +=HIG "������Ů(jiutian xuannv)               ������������            100%                   ��1000.00\n";
  msg +=HIG "��ɷ����(tiansha guxing)               ������������            100%                   ��1000.00\n";
  msg +=HIG "ʮ�����(shiji shenbing)               ����    ����            100%                   ��500.00\n";
  msg +=HIG "����쾧(tian jing)                    ����    ����            100%                   ��500.00\n";
  msg +=HIG "���ϻ�ͯ��(huantong dan)               ����    ����            100%                   ��500.00\n";
  msg +=HIG "�����ý�(jiushi haojian)               ת��    ��Ʒ            100%                   ��200.00\n";
  msg +=HIG "�� �� ��(qinlin bi)                    ת��    ��Ʒ            100%                   ��200.00\n";
  msg +=HIW "Ů � ʯ(nvwa shi)                     ת��    ��Ʒ            100%                   ��200.00\n";
  msg +=HIW "�� �� Ȧ(jingang quan)                 ת��    ��Ʒ            100%                   ��200.00\n";NOR;

  write(msg);
  return 1;

}

int do_pull(string arg)
{
        object me,ob;
        int rmb;
        me = this_player();

        if (! arg || (arg != "card" && arg != "zhyx card"))
                return 1;

        if (me->is_busy())
        {
                return notify_fail("����æ���ء�\n");
        }
        // �жϿ�Ƭ�Ƿ�δȡ��
        if (me->query("temp/insert") && me->query("temp/can_pull"))
        {      
                rmb = me->query("rmb");
                tell_object(me, HIC "��Ŀǰ�Ĵ��Ϊ" + chinese_number(rmb) + "Բ����ҡ�\n" NOR);
                write(HIW "�㽫��Ƭ���л��Զ��ۻ�����ȡ����\n" NOR);
                ob = new("/clone/gift/hycard.c");
                ob->move(me);
                me->delete("temp/insert");
                return 1;
        }
        write(HIR "��������!\n" NOR);
        return 1;
}


int do_buy(string arg)
{
    object me, ob;
    int rmb, feng,sun,lighting,water;
    
    me = this_player();
    rmb = me->query("rmb");
    
    if (! arg || arg == "") return 1;
    
    if (arg == "tian jing")
    {
          if (rmb < 500)
          { 
              write("�Բ���,��Ŀ�������Ѳ���,�뾡���ֵ!\n" NOR);
              return 1;
          }
          ob = new("/d/death/obj/tianjing");
          ob->move(me);
          me->add("rmb", -500); 
          write(HIG "������һ������쾧��\n" NOR);       
    } 
  else  if (arg == "zhenming tianzi")
    {
          if (rmb < 1000)
          { 
              write("�Բ���,��Ŀ�������Ѳ���,�뾡���ֵ!\n" NOR);
              return 1;
          }
          me->set("special_skill/youth", 1);
          me->set("special_skill/emperor", 1);
          me->add("rmb", -1000);  
          write(HIG "���������������������ԣ�\n" NOR);
    }    
    else  if (arg == "jiutian xuannv")
    {
          if (rmb < 1000)
          { 
              write("�Բ���,��Ŀ�������Ѳ���,�뾡���ֵ!\n" NOR);
              return 1;
          }
          me->set("special_skill/youth", 1);
          me->set("special_skill/queen", 1);
          me->add("rmb", -1000);  
          write(HIG "�����¾�����Ů�������ԣ�\n" NOR);
    }      
    else  if (arg == "tiansha guxing")
    {
          if (rmb < 1000)
          { 
              write("�Բ���,��Ŀ�������Ѳ���,�뾡���ֵ!\n" NOR);
              return 1;
          }
          me->set("special_skill/youth", 1);
          me->set("special_skill/lonely", 1);
          me->add("rmb", -1000);  
          write(HIG "��������ɷ�����������ԣ�\n" NOR);
    } 
    else if (arg == "huantong dan")
    {
          if (rmb < 500)
          { 
              write("�Բ���,��Ŀ�������Ѳ���,�뾡���ֵ!\n" NOR);
              return 1;
          }
          ob = new("/d/zhuanshi/obj/huantong");
          ob->move(me);
          me->add("rmb", -500);  
          write(HIG "������һ�ŷ��ϻ�ͯ����\n" NOR);
    }    
    else if (arg == "jiushi haojian")
    {
          if (rmb < 200)
          { 
              write("�Բ���,��Ŀ�������Ѳ���,�뾡���ֵ!\n" NOR);
              return 1;
          }
          ob = new("/d/zhuanshi/obj/jiushi");
          ob->move(me);
          me->add("rmb", -200);  
          write(HIG "������һ�Ѿ����ý���\n" NOR);
    }        
    else if (arg == "�� �� ��")
    {
          if (rmb < 200)
          { 
              write("�Բ���,��Ŀ�������Ѳ���,�뾡���ֵ!\n" NOR);
              return 1;
          }
          ob = new("/d/zhuanshi/obj/qilin");
          ob->move(me);
          me->add("rmb", -200);  
          write(HIG "������һ������ۣ�\n" NOR);
    }        
    else if (arg == "nvwa shi")
    {
          if (rmb < 200)
          { 
              write("�Բ���,��Ŀ�������Ѳ���,�뾡���ֵ!\n" NOR);
              return 1;
          }
          ob = new("/d/zhuanshi/obj/shi");
          ob->move(me);
          me->add("rmb", -200);        
          write(HIG "������һ��Ů�ʯ��\n" NOR);
    }        
    else if (arg == "tian jing")
    {
          if (rmb < 200)
          { 
              write("�Բ���,��Ŀ�������Ѳ���,�뾡���ֵ!\n" NOR);
              return 1;
          }
          ob = new("/d/zhuanshi/obj/quan");
          ob->move(me);
          me->add("rmb", -200);        
          write(HIG "������һ�����Ȧ��\n" NOR);
    }        
    else if (arg == "shiji shenbing")
    {
          if (rmb < 500)
          { 
              write("�Բ���,��Ŀ�������Ѳ���,�뾡���ֵ!\n" NOR);
              return 1;
          }   
          write(HIG "�������WIZ��ϵ��WIZ����������������\n" NOR);      
    }                
    else{
          write(HIR "��������\n" NOR);
          return 1;
    }
    write(HIG "�������! �뿪ǰ��ǵ�ȡ��(pull)��Ƭ��\n");
    rmb = me->query("rmb");
    tell_object(me, HIC "��Ŀǰ�Ĵ��Ϊ" + chinese_number(rmb) + "Բ����ҡ�\n" NOR);
    if (me->query("rmb") < 10) 
          write(HIY "�������Ѳ��࣬Ϊ�����������Ĳ��㣬�뼰ʱ��ֵ��\n" NOR);
    return 1;
}


