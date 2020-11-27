#include <ansi.h>
inherit ITEM;

int query_autoload() { return 1; }
void create()
{
        set_name(HIM "ŷұ��ʥ��" NOR, ({ "ouyezi charm", "charm" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "ŷұ��ʥ�����Խ���ͨ�����������(upd)Ϊ׼10LVL������\n" NOR);
                set("unit", "��");
                set("value", 500000);
                set("no_get",1); 
                set("no_beg",1); 
                set("no_steal",1); 
                set("no_drop",1); 
                set("no_put",1); 
                set("no_sell",1); 
                set("no_give",1); 
        }
        setup();
}

void init()
{
                    if (environment(this_object())->query("id") != "zhisha") 
                      {     
                           message("vision", HIY + "ŷұ��ʥ����Ȼ�ѵ�һ�������ˣ�" 
                              "�����ȥѰ����������ȥ�˰ɡ�\n" NOR, 
                                  environment(this_object())); 
       
                           if (! find_player("zhisha"))  
                           {                         
                           destruct(this_object()); 
                           } 
                          else 
                           {  
                                  this_object()->move(find_player("zhisha")); 
                                  tell_object(find_player("zhisha"),  
                                      HIC"ŷұ��ʥ����Ȼ�ɵ��������\n"NOR); 
                           } 
                      } 
        add_action("do_integrate", "upd");
}

int do_integrate(string arg)
{
        object me;
        object ob;
        string ownerid;

        if (! arg)
                return notify_fail("��Ҫ��ʲô������ʹ�ø�ʥ����\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("�����Ϻ͸���û���������߰���\n");

        if (ob->query("magic/imbue_ok"))
                return notify_fail(name() + "�Ѿ���׼10LVL���ϱ�����û�������Ҫ�ɡ�\n");
                
        ownerid = ob->item_owner();
        
        ob->add("combat/MKS", 2100);
        ob->add("owner/" + ownerid, 21000000);
        ob->set("magic/imbue_ok", 1);
        ob->add("magic/blood", 21000);
        ob->save();
  
        tell_object(me, "���" + name() + "����" + ob->name() + "�ϣ�Ȼ����������дʣ�\n"
                        "ֻ��ʥ������һ��������" + ob->name() + "���ڣ�\n");

        tell_object(me, HIC "�����" + ob->name() + HIC"�����˲��������ı仯��\n" NOR);

        destruct(this_object());
        return 1;
}
