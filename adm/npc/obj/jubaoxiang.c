// write by yeer
// update by Lonely 2005.1
// xiang.c 

#include <ansi.h> 

inherit ITEM;
inherit F_SAVE;

#define TO_STORE(x, y) (["name" : ob->query("name"), "id" : ob->query("id"), "file" : base_name(ob), "amount" : x, "sign" : y])

static int load;
mapping *store;
mapping *data_dbase;
mapping *temp_dbase;

int do_store(string arg);
int do_take(string arg);
int do_lock(string arg);
int do_open(string arg);
int do_view(string arg);
int get_passwd(string pass, object ob);
int confirm(string yn, object me);
int set_passwd(string pass, object ob);
int store_item(object me, object obj, int amount);
int store_data(object me, object ob, int sn);
int compare_mapping(mapping m1, mapping m2);
int compare_array(mixed *a1, mixed *a2);

void create()
{
        set_name(HIM "�۱���" NOR, ({ "ju baoxiang", "baoxiang", "xiang" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {          
                set("long", HIW "һ�����ܱ�Ե���������ع⻷�����ӣ���˵"
                                "���Խ����������ƵĴ棨store����ȥ,����"
                                "��ʧ��������ʲôʱ�򶼿���ȡ��take����"
                                "����������ʹ����������lock��������" NOR);
                                
                set("value", 100);              
                set("unit", "��");
                set("no_get", 1);
        }
        setup();
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (query("open"))
        {
                msg += HIW "����Ŀǰ�ǿ��ŵģ������ֱ�Ӳ鿴��view�����������Ʒ��" NOR;
                return sort_string(msg, 38, 0);
        } else
        {
                if (query("closed"))
                        msg += HIW "����Ŀǰ�ǹ��ŵģ��ƺ�������������������Ҫ�ȴ�"
                        "����open�����Ӳſ��Բ鿴��view�����������Ʒ��" NOR;
                else
                        msg += HIW "����Ŀǰ�ǹ��ŵģ�����û����������������Ҫ�ȴ�"
                        "����open�����Ӳſ��Բ鿴��view�����������Ʒ��" NOR;

                return sort_string(msg, 38, 0);
        }
}

void init() 
{
        string owner;
        object env; 

        if (! load) 
        {       
                env = environment(this_object());  
                if (stringp(owner = env->query("room_owner_id"))) 
                        set("owner", owner);
                        
                restore();
                load = 1;                    
        }
        
        add_action("do_view",  ({ "view",  "cha" }));
        add_action("do_store", ({ "store", "cun" }));
        add_action("do_take",  ({ "take",  "qu"  }));
        add_action("do_lock",  ({ "lock",  "suo" }));        
        add_action("do_open",  ({ "open",  "kai" }));        
}

int do_view(string arg)
{
        object me;
        mixed ob_name_real_len;
        string msg, ob_name;

        me = this_player();

        if (! id(arg))
                return notify_fail("��Ҫ�鿴ʲô��\n");
                
        if (query("open") != 1 && ! wizardp(me)) 
                return notify_fail("���Ȱ����Ӵ򿪲��ܲ鿪��Ʒ��\n");

        if (! store || sizeof(store) < 1)
                return  notify_fail("��Ŀǰû�д���κ���Ʒ�������\n");     

        msg = HIW "\nĿǰ���ŵ���Ʒ�У�\n���  ��Ʒ                                      ����\n"
                  "����������������������������������������������������\n" NOR;
              
        for (int i = 0; i < sizeof(store); i++) 
        {
                ob_name = filter_color(store[i]["name"] + "(" + store[i]["id"] + ")"); 
                ob_name_real_len = color_len(store[i]["name"] + "(" + store[i]["id"] + ")");
                msg += sprintf("[%2d]  %-" + (36 + ob_name_real_len) + "s     %5d\n", 
                               i + 1, store[i]["name"] + "(" + store[i]["id"] + ")",  
                               store[i]["amount"]);
                if (store[i]["amount"] == 0)
                        store[i] = 0;
        }
        msg += HIW "����������������������������������������������������\n" NOR;
        this_player()->start_more(msg);
        store -= ({ 0 });
        return 1;
}        

int do_open(string arg)
{
        string f, pass, new_pass, st_pass;
        object me;
        int st_stat;

        me = this_player();

        if (! id(arg))
                return notify_fail("��Ҫ���ʲô��\n");
                
        if (query("closed") && this_object()->query("owner") != me)
        {
                write("�����Ѿ����˰����������뿪�����룺");
                input_to((: get_passwd :), me);    
                return 1;
        }
        
        set("open", 1);
        set("closed", 0);
        write(HIG "�����Ѿ��ɹ��򿪣������� view �鿴������װ�Ķ�����\n" NOR);
        return 1;
}

int get_passwd(string pass, object ob)
{               
        if (crypt(pass, query("passwd")) == query("passwd")) 
        {
                set("open", 1);
                set("closed", 0);
                write(HIG "�����Ѿ��ɹ������������� view �鿴������װ�Ķ�����\n" NOR);
                return 1;
        } else 
        { 
                write("���������˶���������ԣ�\n");
                return 1;
        }
}

int do_lock(string arg)
{
        string f, pass, new_pass, st_pass;
        object me;
        int st_stat;

        me = this_player();

        if (! id(arg))
                return notify_fail("��Ҫ������ʲô��\n");
        
        if (query("closed"))
                return notify_fail("�����Ѿ����˰�����\n");
                        
        set("open", 0);
        
        if (this_object()->query("owner") != me->query("id"))
        {
                if (query("passwd"))
                        set("closed", 1);
                        
                write("������Ӻ���" + (query("passwd") ? "�������˰�����" : "��") + "\n");
                return 1;
        }   
        
        write("�����Ѿ����ϣ�����Ҫ�����Ӽ��ϰ����𣿣�" HIR "y" HIG "/" HIY "n" HIG "��\n" NOR);
        input_to((: confirm :), me);
        return 1; 
}

int confirm(string yn, object me)
{
        if (upper_case(yn) == "Y") 
        {                 
                write(HIW "���趨���Ӱ��������룺" NOR);
                input_to((: set_passwd :), me);
                
                return 1;
        } else 
        {
                write(HIG "��ѡ���˷����Ӱ�����\n" NOR);
                return 1;
        }
}

int set_passwd(string pass, object ob)
{ 
        write("\n");

        if (strlen(pass) < 5)
        {
                write("��������ĳ�������Ҫ�����Ԫ�����������İ������룺\n");
                input_to((: set_passwd :), ob);
                return 1;
        }
        
        set("closed", 1);             
        set("passwd", crypt(pass, 0));
        save();
        write(HIG "�����Ѿ��ɹ����ϣ����ס���趨�����룡\n" NOR);
        return 1;
}

int do_take(string arg)
{
        object me, ob;
        int i, j, sn, amount, amount1;
        mapping data;
        string *ks;

        me = this_player();

        if (query("open") != 1 && ! wizardp(me)) 
                return notify_fail("�����Ѿ����������Ƚ�����\n");

        if (! arg || sscanf(arg, "%d %d", amount, sn) != 2) 
                return notify_fail("��ʽ�������� take ���� ��� ��ȡ����Ʒ��\n");

        if (amount < 1 || amount > 2000) 
                return notify_fail("ÿ��ȡ��Ʒ����������С��һͬʱҲ���ܴ�����ǧ��\n");
                
        if (sn < 1) return notify_fail("��Ҫȡ�ڼ�����Ʒ��\n");
        
        if (! store || sizeof(store) < 1 || sn > sizeof(store)) 
                return notify_fail("���������û�д��������Ʒ��\n");        
                
        if (amount > store[sn-1]["amount"]) 
                return notify_fail("������Ʒ��û����ô�����\n");

        ob = new(store[sn-1]["file"]);
        if (me->query_encumbrance() + ob->query_weight() * amount > me->query_max_encumbrance()) 
        {
                tell_object(me, "��ĸ��ز������޷�һ��ȡ����ô����Ʒ��\n");
                destruct(ob);
                return 1;
        }

        store[sn-1]["amount"] -= amount;

        if (ob->query_amount()) 
        {
                if (store[sn-1]["amount"] == 0) 
                {
                        store[sn-1] = 0;
                        store -= ({ 0 });
                }
                ob->set_amount(amount);
                ob->move(me);
                save();
                                
                message_vision("$N��������ȡ��һ" +
                                ob->query("unit") + ob->query("name") + "��\n", me);
                return 1;
        }
        
        destruct(ob);
        
        amount1 = amount;
                             
        while (amount1--) 
        {
                ob = new(store[sn-1]["file"]);
                if (data_dbase && sizeof(data_dbase) > 0)
                {
                        for (i = 0; i < sizeof(data_dbase); i++)
                        {
                                if (data_dbase[i]["sign"] == store[sn-1]["sign"])
                                {
                                        data = data_dbase[i];
                                        ks = keys(data);
                                        for (j = 0; j < sizeof(ks); j++) 
                                        {
                                                if (ks[j] == "sign") continue;                            
                                                ob->set(ks[j], data[ks[j]]);
                                        }                                        
                                        data_dbase[i] = 0;
                                }
                        }
                        data_dbase -= ({ 0 });
                }
                if (temp_dbase && sizeof(temp_dbase) > 0)
                {
                        for (i = 0; i < sizeof(temp_dbase); i++)
                        {
                                if (temp_dbase[i]["sign"] == store[sn-1]["sign"])
                                {
                                        data = temp_dbase[i];
                                        ks = keys(data);
                                        for (j = 0; j < sizeof(ks); j++) 
                                        {
                                                if (ks[j] == "sign") continue;                            
                                                ob->set_temp(ks[j], data[ks[j]]);
                                        }
                                        temp_dbase[i] = 0;
                                }
                        }
                        temp_dbase -= ({ 0 });  
                }   
                
                if(ob->short() != store[sn-1]["name"] + "(" + store[sn-1]["id"] + ")") 
                { 
                        amount1++;
                        destruct(ob);
                        continue;
                }                           
                ob->move(me);
        }

        message_vision("$N��������ȡ��" + chinese_number(amount) + 
                        ob->query("unit") + ob->query("name") + "��\n", me);
                                
        if (store[sn-1]["amount"] == 0) 
        {
                store[sn-1] = 0;
                store -= ({ 0 });
        }
        save();
        return 1;
}

int do_store(string arg)
{
        int i, amount;
        string item;
        object me, ob1, ob2, *inv;

        me = this_player();

        if (! arg) return notify_fail("��Ҫ���ʲô������\n");
        
        if (query("open") != 1 && ! wizardp(me)) 
                return notify_fail("�����Ǻ��ϵģ����ȴ򿪣�open�����ٷ�����Ʒ��\n");

        if (store && sizeof(store) > 200)
                return notify_fail("�������ֻ�ܴ������ٸ����ӣ����������Ѿ����ˡ�\n");
                
        if (sscanf(arg, "%d %s", amount, item) == 2) {

                if(! objectp(ob1 = present(item, me)))
                        return notify_fail("������û������������\n");

                /*
                if (! inherits(ITEM, ob1) && ! inherits(COMBINED_ITEM, ob1))
                        return notify_fail("�Բ����㲻�ܴ�Ÿ���Ʒ��\n");
                */
                if (member_array(ITEM + ".c", deep_inherit_list(ob1)) == -1 &&
                    member_array(COMBINED_ITEM + ".c", deep_inherit_list(ob1)) == -1)
                        return notify_fail("�Բ����㲻�ܴ�Ÿ���Ʒ��\n");

                if(member_array(MONEY+ ".c", deep_inherit_list(ob1)) != -1)
                        return notify_fail("Ҫ��Ǯ��ȥǮׯ�ɡ�\n");

                if(base_name(ob1) == "/clone/misc/corpse")
                        return notify_fail("���Ӳ�����" + ob1->query("name") + "�������Լ����ƴ���\n");
                        
                if (! ob1->query_amount())
                        return notify_fail(ob1->name() + "���ܱ��ֿ���š�\n");

                if (amount < 1)
                        return notify_fail("����������������һ����\n");

                if (amount > ob1->query_amount())
                        return notify_fail("��û����ô���" + ob1->name() + "��\n");

                else 
                if (amount == (int)ob1->query_amount())
                        return store_item(me, ob1, amount);

                else 
                {
                        ob1->set_amount((int)ob1->query_amount() - amount);
                        ob2 = new(base_name(ob1));
                        ob2->set_amount(amount);
                        if(! store_item(me, ob2, amount)) 
                        {
                                ob2->move(me);
                                return 0;
                        }
                        return 1;
                }
        }
 
        if (arg == "all") 
        {

                inv = all_inventory(me);

                for(i = 0; i < sizeof(inv); i++) 
                        do_store(inv[i]->query("id"));

                return 1;
        }

        if(! objectp(ob1 = present(arg, me)))
                return notify_fail("������û������������\n");

        if (member_array(ITEM + ".c", deep_inherit_list(ob1)) == -1 &&
            member_array(COMBINED_ITEM + ".c", deep_inherit_list(ob1)) == -1)
                return notify_fail("�Բ����㲻�ܴ�Ÿ���Ʒ��\n");      

        if(member_array(MONEY + ".c", deep_inherit_list(ob1)) != -1)
                return notify_fail("Ҫ��Ǯ��ȥǮׯ�ɡ�\n");

        if(base_name(ob1) == "/clone/misc/corpse")
                return notify_fail("���Ӳ�����" + ob1->query("name") + "�������Լ����ƴ���\n");

        if (ob1->query_amount()) 
                return do_store(ob1->query_amount() + " " + arg);

        store_item(me, ob1, 1);
        return 1;
}

int store_item(object me, object ob, int amount)
{
        object obj;
        int i, n, sn;

        if (ob->query("unique") || ! clonep(ob) || 
            ob->query("id") == "pass")
        {
                tell_object(me, "������Ʒ���ܴ�����������ġ�\n");
                return 1;
        }

        switch((string)ob->query("equipped")) 
        {
        case "worn":
                tell_object(me, ob->name() + "���������������ܴ�š�\n");
                return 1;
        case "wielded":
                tell_object(me, ob->name() + "�����Ƚ��װ�����ܴ�š�\n");
                return 1;
        }

        if (! objectp(ob)) 
        {
                error("no this object!\n");
                return 1;
        }
        
        if (sizeof(all_inventory(ob))) 
        {
                tell_object(me, "�����Ȱ�" + ob->query("name") + "����Ķ������ó�����\n");
                return 1;
        }
        
        if (! store) store = ({});
        
        n = sizeof(store);

        obj = new(base_name(ob));
        if (ob->query("startroom") == "/adm/npc/obj/xiang")
                ob->delete("startroom"); // Ϊ������̶ԭ�е����Ӷ����

        if (! ob->query_amount()) 
        { 
                if (! compare_mapping(ob->query_entire_temp_dbase(), obj->query_entire_temp_dbase()) || 
                    ! compare_mapping(ob->query_entire_dbase(), obj->query_entire_dbase()))
                {                        
                        sn = time() + random(99999999);
                        store += ({TO_STORE(amount, sn)});
                        store_data(me, ob, sn);
                        save();
                
                        message_vision("$N����" + chinese_number(amount) + ob->query("unit") + 
                                        ob->query("name") + "�������\n", me);             
                        destruct(ob);
                        destruct(obj);
                        return 1;
                } 
        }
        destruct(obj);        
        for (i = 0; i < n; i++) 
        {
                if (store[i]["id"] == ob->query("id") && 
                    store[i]["name"] == ob->query("name") && 
                    store[i]["file"] == base_name(ob)) 
                {
                        store[i]["amount"] += amount;
                        
                        message_vision("$N����" + (amount > 1 ? "һ" : chinese_number(amount)) +
                                        ob->query("unit") + ob->query("name") + "�������\n", me);                               
                        destruct(ob);
                        save();
                        return 1;
                }
        }

        store += ({TO_STORE(amount, 0)});
        save();

        message_vision("$N����" + (amount > 1 ? "һ" : chinese_number(amount)) +
                        ob->query("unit") + ob->query("name") + "�������\n", me);           

        destruct(ob);
        return 1;
}

int store_data(object me, object ob, int sn)
{
        mapping data;

        if (! data_dbase) 
                data_dbase = ({});
        data = ob->query_entire_dbase();
        data += ([ "sign" : sn ]);
        data_dbase += ({data});
        
        if (! temp_dbase)
                temp_dbase = ({});
                
        data = ob->query_entire_temp_dbase();
        
        if (! data) return 1;
        
        data += ([ "sign" : sn ]);        
        temp_dbase += ({data});
        
        return 1;
}

int compare_mapping(mapping m1, mapping m2)
{
        string index, m_type;

        if (! m1 && ! m2 ) 
                return 1;

        if (sizeof(m1) != sizeof(m2)) 
                return 0;

        foreach (index in keys(m1)) 
        {
                m_type = typeof(m1[index]);
                if (m_type != typeof(m2[index])) 
                        return 0;
                if (m_type == "mapping" && ! compare_mapping(m1[index], m2[index])) 
                        return 0;                        
                if (m_type == "array" && ! compare_array(m1[index], m2[index])) 
                        return 0;
                if (m1[index] != m2[index]) 
                        return 0;
        }
        return 1;
}

int compare_array(mixed *a1, mixed *a2)
{
        int a_size;
        string a_type;

        if (! a1 && ! a2) 
                return 1;

        a_size = sizeof(a1);
        if (a_size != sizeof(a2)) 
                return 0;
        
        for (int i = 0; i < a_size; i++) 
        {
                a_type = typeof(a1[i]);
                if (a_type != typeof(a2[i])) 
                        return 0;
                if (a_type == "mapping" && !compare_mapping(a1[i], a2[i])) 
                        return 0;
                if (a_type == "array" && !compare_array(a1[i], a2[1])) 
                        return 0;
                if (a1[i] != a2[i]) 
                        return 0;
        }
        return 1;
}

int remove()
{
        save();
}

public void mud_shutdown() 
{ 
        save(); 
} 

string query_save_file() 
{
        string id;

        if (! stringp(id = query("owner")) ) return 0;
        return DATA_DIR + "room/" + id + "/" + "xiang";
}
