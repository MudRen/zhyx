//��ҵϵͳ�ܿس���
//edit by smallfish

#include <ansi.h>
#include <getconfig.h>

/*
���ļ�Ϊ��ҵϵͳ�кڵ�����ɳ���
���ļ��ṩ�����ļ����ã�
/cmds/wiz/openshop.c			��ʦ���źڵ�ָ��
/cmds/wiz/closeshop.c		��ʦ�رպڵ�ָ��
/cmds/std/listshop.c			��ѯ�ڵ��б�ָ��
/feature/heidian_huoji.c		��Ƴ���ӿ��ļ�
/feature/heidian.c			�ڵ����ӿ��ļ�

�ڵ��Լ���Ƶĳ�����·����/clone/heidian
�ڵ��Ʋ���*.o��ʽ���ļ��洢���洢�ļ�����ڣ�/data/shop
�ڵ��Ƽ̳��ļ���/feature/heidian_huoji.c
�ڵ�����Ҫ�洢������
string owner:			����ID
string shop_id:		������ݴ����ļ���
int shop_type			���״̬��0��ʾ�رգ�
mapping vendor_goods:	����۸�keysΪ�����base_name
mapping vendor_goods_num:	��������������keysΪ�����base_name
int all_vendor_goods:	���л��������ܺ�
mapping vip:			������ۿۣ�keysΪ�����id
string *unwelcome:		�ڻ��б�keysΪ�ڻ�id

�ڵ�̳��ļ���/feature/heidian.c
�ڵ���Ҫ������
string owner:			����ID
int shop_type��		�ڵ�״̬��0��ʾ�رգ�
*/

public mapping *query_heidian();						//���غڵ��б�
public int is_chushihua();							//���غڵ��Ƿ�ȫ����ʼ��
private int check_owner(string arg);					//���ڵ����˺ͺڵ��������Ƿ���ͬ
public int change_owner(object me,string arg,string owner);		//�޸ĺڵ�������ڵ����˺ͺڵ������ˣ�
public int is_owner(string owner);						//�鿴���owner�Ƿ�ڵ����
public int close_all(object me);						//�ر����кڵ�
public int close_heidian(object me,string arg);				//�ر�ָ���ڵ�
public int open_all(object me);						//�������кڵ�
public int open_heidian(object me,string arg);				//����ָ���ڵ�
public int reset_all(object me);						//��ʼ�����кڵ�
public int reset_heidian(object me,string arg);				//��ʼ��ָ���ڵ�
public int list_heidian(object me);					//��ѯ�ڵ꣨��listshopָ����ã�
public string do_modify(object obj,object me,string arg);		//�޸ĺڵ��Ƶ�����
public string do_stock(object ob,object me,string arg);		//��۲����ۻ���
public string do_unstock(object ob,object me,string arg);		//ȡ�»���
public string do_list(object ob,object me,string arg);			//��ѯ����
public int do_buy(object obj,object me,string arg);			//�������
private int player_pay(object who, object target, int amount);	//���������ҵ�����Լ�˰��
public string do_jiezhang(object ob,object me);				//���ʣ��ڵ����˲�����ʱ��ĺڵ����룩
public string list_vip(object ob,object me);				//��ѯ����б�
public string do_vip(object ob,object me,string arg);			//����|ȡ�� ���
public string list_unwelcome(object ob,object me);			//��ѯ�ڻ��б�
public string do_unwelcome(object ob,object me,string arg);		//����|ȡ�� �ڻ�
private void destruct_it(object ob);					
public int do_long(object me);						//�޸ĺڵ�����
public int do_short(object me,string arg);				//�޸ĺڵ�����
private int get_long(string msg,string arg,object me);			//¼��ڵ���������do_long�������ã�
private varargs int do_saveroom(object me,object the_room);		//�洢�ڵ��ļ�
private int save_room_file(string yn, string file, string str, object me);	//���ڵ��ļ�д��Ӳ��
private int update(object me, string file);				//���±���ڵ�

string *special_props = ({
    "short", "long" });

static mapping *all_heidian = ({
        ([
                "id":             "beijing",
                "name":		"����",
                "start_room":     "beijing_heidian",
                "huoji":          "beijing_huoji",
                "type":           "heidian",
                "price":		3000,
        ]),
        ([
                "id":             "dali",
                "name":		"����",
                "start_room":     "dali_heidian",
                "huoji":          "dali_huoji",
                "type":           "heidian",
                "price":		3000,
        ]),
        ([
                "id":             "yangzhou",
                "name":		"����",
                "start_room":     "yangzhou_heidian",
                "huoji":          "yangzhou_huoji",
                "type":           "heidian",
                "price":		3000,
        ]),
        ([
                "id":             "foshan",
                "name":		"��ɽ",
                "start_room":     "foshan_heidian",
                "huoji":          "foshan_huoji",
                "type":           "heidian",
                "price":		3000,
        ]),
        ([
                "id":             "ruzhou",
                "name":		"����",
                "start_room":     "ruzhou_heidian",
                "huoji":          "ruzhou_huoji",
                "type":           "heidian",
                "price":		3000,
        ]),
        ([
                "id":             "chengdu",
                "name":		"�ɶ�",
                "start_room":     "chengdu_heidian",
                "huoji":          "chengdu_huoji",
                "type":           "heidian",
                "price":		2000,
        ]),
});

public mapping *query_heidian()
{
        return all_heidian;
}

public int is_chushihua()
{
        int i,is_ok;
        object heidian,huoji;

        is_ok = 1;
        for (i = 0;i < sizeof(all_heidian);i++)
        {
                heidian = load_object(HEIDIAN_DIR + all_heidian[i]["start_room"]);
                huoji = load_object(HEIDIAN_DIR + all_heidian[i]["huoji"]);
                if (!heidian || !huoji || heidian->query("shop_type") || huoji->query("shop_type"))
                {
                        is_ok = 0;
                        break;
                }
                else
                {
                        if ((huoji->query("vendor_goods") && sizeof(huoji->query("vendor_goods")) > 0) ||
                             huoji->query("all_vendor_goods") ||
                             heidian->query("owner") != "VOID_HEIDIAN" ||
                             huoji->query("owner") != "VOID_HEIDIAN")
                        {
                                is_ok = 0;
                                break;
                        }
                }
        }
        return is_ok;
}

private int check_owner(string arg)
{
        int i,have_it;
        object the_heidian,the_huoji;
        string heidian_owner,huoji_owner;

        have_it = 0;
        for (i = 0;i < sizeof(all_heidian);i++)
        {
                if (all_heidian[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }
        if (!have_it) return 0;	//û���ҵ�ָ���ĺڵ�
        the_heidian = load_object(HEIDIAN_DIR + all_heidian[i]["start_room"]);
        if (!the_heidian) return 0;
        heidian_owner = the_heidian->query("owner");
        the_huoji = load_object(HEIDIAN_DIR + all_heidian[i]["huoji"]);
        if (!the_huoji) return 0;
        huoji_owner = the_huoji->query("owner");
        destruct(the_huoji);	//load_object�������Ǹ�����ļ��ĸ��ƶ���Ϊ����洢���ݳ�������ݻ�
        if (heidian_owner != huoji_owner)
                return 0;
        else
                return 1;
}

public int change_owner(object me,string arg,string owner)
{
        int i,have_it;
        object the_heidian,the_huoji;

        have_it = 0;
        for (i = 0;i < sizeof(all_heidian);i++)
        {
                if (all_heidian[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }
        if (!have_it)
        {
                tell_object(me,"�Բ���" + arg + "�ڵ겢�����ڡ�\n");
                return 1;
        }
        if (!check_owner(arg))
        {
                tell_object(me,"���棺"+arg+"�ڵ����˺ͺڵ������������쳣������ϸ��飡\n");
                log_file("static/heidian",sprintf("%s�ڵ������쳣��ʱ�䣺%s��\n",arg,ctime(time())));
                return 1;
        }
        the_huoji = load_object(HEIDIAN_DIR + all_heidian[i]["huoji"]);
        if (the_huoji)
        {
                the_huoji->set("owner",owner);
                the_huoji->save();
                destruct(the_huoji);
                tell_object(me,arg + "�ڵ��������޸���ϣ�\n");
        } else
        {
                tell_object(me,arg + "�ڵ����ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }
        the_heidian = load_object(HEIDIAN_DIR + all_heidian[i]["start_room"]);
        if (the_heidian)
        {
                the_heidian->set("owner",owner);
                do_saveroom(me,the_heidian);
                tell_object(me,arg + "�ڵ�����޸���ϣ�\n");
        } else
        {
                tell_object(me,arg + "�ڵ��ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }
        return 1;
}

public int is_owner(string owner)
{
        int i;
        object heidian;
        for (i = 0;i < sizeof(all_heidian);i ++)
        {
                heidian = load_object(HEIDIAN_DIR + all_heidian[i]["start_room"]);
                if (!objectp(heidian)) return 0;
                if (heidian->query("owner") == owner) return 1;
        }
        return 0; 
}

public int close_all(object me)
{
        int i;
        for (i = 0;i < sizeof(all_heidian);i++)
                close_heidian(me,all_heidian[i]["id"]);
        return 1;
}

//�رպڵ����޸ĺڵ��Լ���Ƶ�shop_typeΪ0
public int close_heidian(object me,string arg)
{
        int i,have_it;
        object the_heidian,the_huoji;

        have_it = 0;
        for (i = 0;i < sizeof(all_heidian);i++)
        {
                if (all_heidian[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }
        if (!have_it)
        {
                tell_object(me,"�Բ���" + arg + "�ڵ겢�����ڡ�\n");
                return 1;
        }
        if (!check_owner(arg))
        {
                tell_object(me,"���棺"+arg+"�ڵ����˺ͺڵ������������쳣������ϸ��飡\n");
                log_file("static/heidian",sprintf("%s�ڵ������쳣��ʱ�䣺%s��\n",arg,ctime(time())));
                return 1;
        }
        the_huoji = load_object(HEIDIAN_DIR + all_heidian[i]["huoji"]);
        if (the_huoji)
        {
                the_huoji->set("shop_type",0);
                the_huoji->save();
                destruct(the_huoji);
                tell_object(me,arg + "�ڵ��Ƴɹ��رգ�\n");
        } else
        {
                tell_object(me,arg + "�ڵ����ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }
        the_heidian = load_object(HEIDIAN_DIR + all_heidian[i]["start_room"]);
        if (the_heidian)
        {
                the_heidian->set("shop_type",0);
                do_saveroom(me,the_heidian);
                tell_object(me,arg + "�ڵ�ɹ��رգ�\n");
        } else
        {
                tell_object(me,arg + "�ڵ��ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }
        return 1;
}

public int open_all(object me)
{
        int i;
        for (i = 0;i < sizeof(all_heidian);i++)
                open_heidian(me,all_heidian[i]["id"]);
        return 1;
}

//���źڵ����޸ĺڵ��Լ���Ƶ�shop_typeΪ1
public int open_heidian(object me,string arg)
{
        int i,have_it;
        object the_heidian,the_huoji;

        have_it = 0;
        for (i = 0;i < sizeof(all_heidian);i++)
        {
                if (all_heidian[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }
        if (!have_it)
        {
                tell_object(me,"�Բ���" + arg + "�ڵ겢�����ڡ�\n");
                return 1;
        }
        if (!check_owner(arg))
        {
                tell_object(me,"���棺"+arg+"�ڵ����˺ͺڵ������������쳣������ϸ��飡\n");
                log_file("static/heidian",sprintf("%s�ڵ������쳣��ʱ�䣺%s��\n",arg,ctime(time())));
                return 1;
        }
        the_huoji = load_object(HEIDIAN_DIR + all_heidian[i]["huoji"]);
        if (the_huoji)
        {
                the_huoji->set("shop_type",1);
                the_huoji->save();
                destruct(the_huoji);
                tell_object(me,arg + "�ڵ��Ƴɹ����ţ�\n");
        } else
        {
                tell_object(me,arg + "�ڵ����ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }
        the_heidian = load_object(HEIDIAN_DIR + all_heidian[i]["start_room"]);
        if (the_heidian)
        {
                the_heidian->set("shop_type",1);
                do_saveroom(me,the_heidian);
                tell_object(me,arg + "�ڵ�ɹ����ţ�\n");
        } else
        {
                tell_object(me,arg + "�ڵ��ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }
        return 1;
}

public int reset_all(object me)
{
        int i;
        for (i = 0;i < sizeof(all_heidian);i++)
                reset_heidian(me,all_heidian[i]["id"]);
        return 1;
}

//��ʼ���ڵ������
//�رպڵ�
//���úڵ�ͻ�Ƶ�����Ϊ��ֵ
//�����ƵĻ����Լ���ƵĴ��
//�����ƵĹ���ͺڻ�
public int reset_heidian(object me,string arg)
{
        int i,have_it;
        object the_heidian,the_huoji;

        have_it = 0;
        for (i = 0;i < sizeof(all_heidian);i++)
        {
                if (all_heidian[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }
        if (!have_it)
        {
                tell_object(me,"�Բ���" + arg + "�ڵ겢�����ڡ�\n");
                return 1;
        }

        the_huoji = load_object(HEIDIAN_DIR + all_heidian[i]["huoji"]);
        if (the_huoji)
        {
                the_huoji->set("shop_type",0);
                the_huoji->set("owner","VOID_HEIDIAN");
                the_huoji->set("balance",0);
                the_huoji->delete("vendor_goods");
                the_huoji->delete("vendor_goods_num");
                the_huoji->delete("all_vendor_goods");
                the_huoji->delete("vip");
                the_huoji->delete("unwelcome");
                the_huoji->save();
                destruct(the_huoji);
                tell_object(me,arg + "�ڵ��Ƴɹ���ʼ����\n");
        } else
        {
                tell_object(me,arg + "�ڵ����ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }
        the_heidian = load_object(HEIDIAN_DIR + all_heidian[i]["start_room"]);
        if (the_heidian)
        {
                the_heidian->set("shop_type",0);
                the_heidian->set("owner","VOID_HEIDIAN");
                do_saveroom(me,the_heidian);
                tell_object(me,arg + "�ڵ�ɹ���ʼ����\n");
        } else
        {
                tell_object(me,arg + "�ڵ��ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }
        return 1;
}

public int list_heidian(object me)
{
        int i;
        string arg,msg;
        object the_heidian;

        msg = HIC + LOCAL_MUD_NAME() + "�ڵ��б����£�\n" NOR;
        msg += YEL "�ԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡ�\n" NOR;
        for (i = 0;i < sizeof(all_heidian);i++)
        {
                arg = all_heidian[i]["id"];
                if (!check_owner(arg)) continue;
                the_heidian = load_object(HEIDIAN_DIR + all_heidian[i]["start_room"]);
                if (!the_heidian) continue;
                msg += sprintf(HIW "�ڵ�ID��" HIY "%-12s" NOR HIW "�ڵ����ƣ�" HIY "%-10s" NOR HIW "�ڵ����ˣ�" HIY "%-15s" NOR HIW "�ڵ�״̬��" HIY "%s\n" NOR,
                        arg,all_heidian[i]["name"],the_heidian->query("owner"),the_heidian->query("shop_type")?"Ӫҵ��":"�ر�");
        }
        msg += YEL "�ԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡ�\n" NOR;
        msg += HIC "�ܹ� " + HIR + chinese_number(sizeof(all_heidian)) + HIC + " �Һڵꡣ\n" NOR;
        tell_object(me,msg);
        return 1;
}

public string do_modify(object obj,object me,string arg)
{
        string item, msg;
        mapping dbase;

        if (!obj->query("shop_type"))
               return "�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n";
        if(!arg || sscanf(arg,"%s %s",item,msg) != 2)
	        return "SYNTAX: modify ���� ����\n";
        if(CHINESE_D->check_control(msg))
                return "���������п��Ʒ���\n";
        if(CHINESE_D->check_space(msg))
                return "�������費���ո�\n";
        if(CHINESE_D->check_return(msg))
                return "�������費���س�����\n";
        msg = replace_string(msg, "$BLK$", BLK);
        msg = replace_string(msg, "$RED$", RED);
        msg = replace_string(msg, "$GRN$", GRN);
        msg = replace_string(msg, "$YEL$", YEL);
        msg = replace_string(msg, "$BLU$", BLU);
        msg = replace_string(msg, "$MAG$", MAG);
        msg = replace_string(msg, "$CYN$", CYN);
        msg = replace_string(msg, "$WHT$", WHT);
        msg = replace_string(msg, "$HIR$", HIR);
        msg = replace_string(msg, "$HIG$", HIG);
        msg = replace_string(msg, "$HIY$", HIY);
        msg = replace_string(msg, "$HIB$", HIB);
        msg = replace_string(msg, "$HIM$", HIM);
        msg = replace_string(msg, "$HIC$", HIC);
        msg = replace_string(msg, "$HIW$", HIW);
        msg = replace_string(msg, "$NOR$", NOR);
        msg = replace_string(msg, "$S$", BLINK);
	switch(item)
	{
        case "desc":
                if(CHINESE_D->check_length(msg) > 100)
	                return "����̫����\n"; 
	        obj->set("long",msg+ NOR"\n");
	        obj->save();
	        return "�ϣˣ�\n";
        case "nickname" :
                if(CHINESE_D->check_length(msg) > 20)
                        return "����̫����\n";
                obj->set("nickname",msg+NOR);
                obj->save();
                return "�ϣˣ�\n";
        case "title" :
                if(CHINESE_D->check_length(msg) > 20)
                        return "����̫����\n";
                obj->set("title",msg+NOR);
                obj->save();
                return "�ϣˣ�\n";
        case "name" :
                if(CHINESE_D->check_length(msg) > 10)
                        return "����̫����\n";
                dbase = obj->query_entire_dbase();
                dbase["name"] = msg;
                obj->save();
                return "�ϣˣ�\n";
        }
        return "��Ҫ�޸�ʲô��\n";
}

public string do_stock(object ob,object me,string arg)
{
        object obj,goods,obj2;
        int value;
        mapping all_goods,all_goods_num;
        
        if (!ob->query("shop_type"))
               return "�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n";

        if (!arg || !sscanf(arg, "%s value %d", arg,value) == 2) 
                return "stock <����> value * (���� * ����ͭ����Ϊ��λ�ļ۸�)\n";
        if (!value)
                return "stock <����> value * (���� * ����ͭ����Ϊ��λ�ļ۸�)\n";
        if (value > 1500000)
                return "�ڵ������150���ƽ���ͱ���ô�ĺ��˰ɡ�\n";
        if (!(goods = present(arg,me)) || !objectp(goods)) 
                return "�����ϲ�û��������ﰡ��\n";
        if (goods->is_no_clone())
                return "�������������������\n";
        if (goods->is_item_make())
                return "����Լ��������Ʒ������������\n";
        if (goods->is_character()) 
                return "�㲻�ܷ����˿ڣ�\n";
        if (goods->query("money_id")) 
                return "����ˣ�ǮҲ�������ۣ�\n";
        if (ob->query("all_vendor_goods") >= 80) 
                return "��һ��ֻ�ܰ��ϰ�ʮ����������������ֻ����ٰ������ֻ��\n";

        all_goods = ob->query("vendor_goods");
        if (!all_goods) all_goods = ([ ]);
        all_goods_num = ob->query("vendor_goods_num");
        if (!all_goods_num) all_goods_num = ([ ]);

        all_goods[base_name(goods)] = value;
        all_goods_num[base_name(goods)] += 1;

        ob->set("vendor_goods",all_goods);
        ob->set("vendor_goods_num",all_goods_num);
        ob->add("all_vendor_goods",1);

        message_vision(HIW "$N��"+ NOR + goods->name(1) + HIW +"����" + HIY + MONEY_D->price_str(value) + HIW"�ļ۸񣬿�ʼ���ۡ�\n"NOR,me);
        ob->save();
        if (goods->query_amount() && goods->query_amount() > 1) 
        {
                goods->set_amount((int)goods->query_amount() - 1);
                obj2 = new(base_name(goods));
                obj2->set_amount(1);
                destruct(obj2);
        }
        else destruct(goods);
        return "�ϣˣ�\n";
}

public string do_unstock(object ob,object me,string arg)
{
        object obj,goods;
        int i,amount,value,have_it = 0;
        mapping all_goods,all_goods_num;
        string *goods_key,ob_file;
        
        if (!ob->query("shop_type"))
               return "�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n";

        if (!arg) return "unstock <����>\n";

        if (!ob->query("all_vendor_goods")) 
                return "�����ڻ�û�а����κλ��\n";

        all_goods = ob->query("vendor_goods");
        all_goods_num = ob->query("vendor_goods_num");

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED)
                return "�����ϵĶ���̫���ˣ�û���ӻ�����ȡ����������\n";

        all_goods = ob->query("vendor_goods");
        if (!all_goods) all_goods = ([ ]);
        all_goods_num = ob->query("vendor_goods_num");
        if (!all_goods_num) all_goods_num = ([ ]);

        goods_key = keys(all_goods);
        if (arrayp(goods_key))
                for (i = 0; i < sizeof(goods_key); i++) 
                {
                        if (goods_key[i]->id(arg)) 
                                ob_file = goods_key[i];
                        else if (filter_color(goods_key[i]->name(1)) == arg) 
                                ob_file = goods_key[i];
                }

        if (!ob_file)
                return environment(ob)->short() + " �����ϲ�û��������������ϸ�����Ŷ��\n";

        goods = new(ob_file);

	if (!goods)
		return "�Բ��𣬴���Ʒ�����⣬����ϵ��ʦ������\n";

        ob->add("all_vendor_goods",-1);
        all_goods_num[base_name(goods)] -= 1;
        if (all_goods_num[base_name(goods)] == 0)
        {
                map_delete(all_goods,base_name(goods));
                map_delete(all_goods_num,base_name(goods));
        }
        message_vision(HIW "$N��" + NOR + goods->name(1) + HIW + "�ӻ�����ȡ���������ˡ�\n",me);
   
        ob->set("vendor_goods",all_goods);
        ob->set("vendor_goods_num",all_goods_num);
        ob->save();
        if (!goods->move(me))
        {
                goods->move(environment(me));
                tell_object(me,"���Ѿ��ò�����ô�ණ���ˣ�ֻ�ð�" + goods->name(1) + "���ڵ��ϡ�\n");
        }
        return "�ϣˣ�\n";
}

public string do_list(object ob,object me,string arg)
{
        mapping goods,goods_num;
        string *gks;
        object *obs,*inv;
        string msg;
        int i,have_vendor = 0;

        mapping price;
        mapping unit;
        mapping count;
        string  short_name;
        string  prefix;
        string  *dk;

        if (!ob->query("shop_type"))
               return "�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n";

        if (ob->query("unwelcome") && member_array(me->query("id"),ob->query("unwelcome")) != -1)
               return "�Բ����������Ǳ��ڵ겻�ܻ�ӭ�����\n";

        if (!ob->query("all_vendor_goods")) 
                return environment(ob)->short() + " Ŀǰ��û�г����κλ��\n";

        goods = ob->query("vendor_goods");
        if (!goods) goods = ([]);
        goods_num = ob->query("vendor_goods_num");
        if (!goods_num) goods_num = ([]);

        count   = ([]);
        unit    = ([]);
        price   = ([]);
       
        gks = keys(goods);
        for (i = 0; i < sizeof(gks); i++)
        {
                object gob;
                call_other(gks[i], "???");
                if (! objectp(find_object(gks[i])))
                {
                        log_file("user_vendor", sprintf("No found vendor good:%s\n", gks[i]));
                        continue;
                }
                gob = find_object(gks[i]);
                short_name = gob->name(1) + "(" + gob->query("id") + ")";
                if (gob->query("base_unit"))
                        prefix = "base_";
                else
                        prefix = "";
                unit  += ([ short_name : gob->query(prefix + "unit") ]);
                price += ([ short_name : goods[gks[i]] ]);
                count += ([ short_name : goods_num[gks[i]] ]);
        }

        msg = environment(ob)->short() + " Ŀǰ����������Ʒ��\n";
        msg += "-----------------------------------------------------\n";
        dk = sort_array(keys(unit), 1);
        for (i = 0; i < sizeof(dk); i++)
        {
                int p;
                p = price[dk[i]];
                msg += sprintf("%" + sprintf("%d", (30 + color_len(dk[i]))) +
                               "-s��ÿ%s%s" CYN "(�ֻ�%s)\n" NOR, 
                               dk[i], unit[dk[i]], MONEY_D->price_str(p),
                               chinese_number(count[dk[i]]) + unit[dk[i]]);
        }
        msg += "-----------------------------------------------------\n";
        if (me->query("id") == ob->query("owner")) 
                msg += "�ܹ�" + chinese_number(ob->query("all_vendor_goods")) + "�����\n";

        if (ob->query("vip/" + me->query("id")))     
                msg += "���Ǳ��������������л��������" + HIW + chinese_number(ob->query("vip/" + me->query("id"))) + "��" + NOR + "�Żݣ�\n";

        return msg;
}       

public int do_buy(object obj,object me,string arg)
{
        mapping goods,goods_num;
        int amount;
        int value, val_factor;
        string ob_file,*goods_key;
        object *obs,ob,env;
        string my_id;
        int i;
        
        if (!obj->query("shop_type"))
        {
               tell_object(me,"�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n");
               return 1;
        }

        if (obj->query("unwelcome") && member_array(me->query("id"),obj->query("unwelcome")) != -1)
        {
               tell_object(me,"�Բ����������Ǳ��ڵ겻�ܻ�ӭ�����\n");
               return 1;
        }

        if(me->is_busy())
        {
                tell_object(me,"ʲô�¶��õ���æ����˵�ɣ�\n");
                return 1;
        }
        if (! arg)
        {
                tell_object(me,"ָ���ʽ��buy <thing>\n");
                return 1;
        }

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED)
        {
                tell_object(me,"�����ϵĶ���̫���ˣ��ȴ���һ���������ɡ�\n");
                return 1;
        }

        goods = obj->query("vendor_goods");
        if (!goods) goods = ([]);
        goods_num = obj->query("vendor_goods_num");
        if (!goods_num) goods_num = ([]);

        goods_key = keys(goods);
        if (arrayp(goods_key))
                for (i = 0; i < sizeof(goods_key); i++) 
                {
                        if (goods_key[i]->id(arg)) 
                                ob_file = goods_key[i];
                        else if (filter_color(goods_key[i]->name(1)) == arg) 
                                ob_file = goods_key[i];
                }

        if (!ob_file)
        {
                tell_object(me,environment(obj)->short() + " ��û�г����������\n");
                return 1;
        }

        value = goods[ob_file];

        //����ǹ���������Ż�
        if (obj->query("vip/" + me->query("id")))
                value = value * obj->query("vip/" + me->query("id")) / 10;

        ob = new(ob_file);

	if (!ob)
	{
		tell_object(me,"�Բ��𣬴���Ʒ�����⣬����ϵ��ʦ������\n");
		return 1;
	}

        call_out("destruct_it", 0, ob);
 
        switch (player_pay(me,obj,value))
        {
        case 0:
                tell_object(me,CYN + "��⵰��һ�ߴ���ȥ��\n" NOR);
                return 1;
        case 2:
                tell_object(me,CYN + "������û����Ǯ������Ʊ"+NOR+obj->name(1)+CYN+"���Ҳ�����\n" NOR);
                return 1;
        default:
                if (ob->query_amount())
                {
                        message_vision("$N��$n����������" + ob->short() + "��\n",
                                        me, obj);
                }
                else
                {
                        message_vision("$N��$n����������һ" + ob->query("unit") + 
                	               ob->query("name") + "��\n",
			               me, obj);
                }
                ob->move(me, 1);
                goods_num[ob_file] -= 1;
                if (goods_num[ob_file] == 0) 
                {
                        map_delete(goods,ob_file);
                        map_delete(goods_num,ob_file);
                }
                obj->set("vendor_goods",goods);
                obj->set("vendor_goods_num",goods_num);
                obj->add("all_vendor_goods",-1);
        }
        me->start_busy(1);
        obj->save();
        return 1;
}

private int player_pay(object who, object target, int amount)
{
       object t_ob, g_ob, s_ob, c_ob, owner;
       int tc, gc, sc, cc, left;
       int v;
       int pay_amount;

	seteuid(getuid());

	if (amount >= 100000 && t_ob = present("cash_money", who))
		tc = t_ob->query_amount();
	else
	{
		tc = 0;
		t_ob = 0;
	}

	if (g_ob = present("gold_money", who))
		gc = g_ob->query_amount();
	else
		gc = 0;

	if (s_ob = present("silver_money", who))
		sc = s_ob->query_amount();
	else
		sc = 0;

	if (c_ob = present("coin_money", who))
		cc = c_ob->query_amount();
	else
		cc = 0;
	
	v = cc + sc * 100 + gc * 10000;

	if (amount < 100000 && v < amount)
	{
		if (present("cash_money", who))
			return 2;
		else
			return 0;
	}

	v += tc * 100000;

	if (v < amount) 
		return 0;
	else {
		left = v - amount;
		if (tc)
		{
			tc = left / 100000;
			left %= 100000;
		}
		gc = left / 10000;
		left = left % 10000;
		sc = left / 100;
		cc = left % 100;

		if (t_ob && ! g_ob && gc)
		{
			g_ob = new(GOLD_OB);
			g_ob->move(who, 1);
		}

		if (t_ob)
			t_ob->set_amount(tc);
		if (g_ob)
			g_ob->set_amount(gc);
		else sc += (gc * 100);
		if (s_ob)
		 	s_ob->set_amount(sc);
		else if (sc) {
			s_ob = new(SILVER_OB);
			s_ob->set_amount(sc);
			s_ob->move(who, 1);
		}
		if (c_ob)
			c_ob->set_amount(cc);
		else if (cc) {
			c_ob = new(COIN_OB);
			c_ob->set_amount(cc);
			c_ob->move(who, 1);
		}

              //����˰�ʣ�ÿ30���ƽ����5%��˰
              if (amount > 1200000) 
                     pay_amount = amount*3/4;
              else if (amount > 900000)
                     pay_amount = amount*4/5;
              else if (amount > 600000)
                     pay_amount = amount*17/20;
              else if (amount > 300000)
                     pay_amount = amount*9/10;
              else pay_amount = amount*19/20;
  
              if (owner = find_player(target->query("owner")))
              {
                     owner->add("balance",pay_amount);
                     if (query_ip_number(owner) != query_ip_number(who))
                             owner->add("vendor_score",pay_amount/10000);
              } else target->add("balance",pay_amount);
              return 1;
	}
}

public string do_jiezhang(object ob,object me)
{
       int amount;
       if (!ob->query("shop_type"))
               return "�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n";

       amount = (int)ob->query("balance");
       if (amount < 1)
              return "�����ڵ�ʱ��û���κε����롣\n";
       me->add("balance",amount);
       me->add("vendor_score",amount/10000);
       tell_object(me,HIY "��������ʱ������룺" + MONEY_D->price_str(amount) + "������ȫ��ת���������š�\n");
       ob->set("balance",0);
       ob->save();
       return "�ϣ�\n";
}

public string list_vip(object ob,object me)
{
        int i;
        string msg,*vip_key;
        mapping vip;

        if (!ob->query("shop_type"))
               return "�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n";

        vip = ob->query("vip");
        if (!vip || sizeof(vip) < 1)
        {
                msg = "����û�ж����κεĹ����\n";
                msg += "������ͨ��vip <id> <num>����ӹ��������num 1--9��ʾ1--9�ۣ�num 10��ʾȡ������ʸ�\n";
                return msg;
        }
        msg = HIY "��������Ĺ����������ң�\n" NOR;
        msg += "------------------------------\n";
        vip_key = sort_array(keys(vip),1);
        for (i = 0;i < sizeof(vip_key);i++)
        {
                msg += sprintf(HIY"%-20s  " HIW "%s��\n" NOR, vip_key[i], chinese_number(vip[vip_key[i]]));
        }
        msg += "------------------------------\n";
        msg += HIY "�ܹ�" + sizeof(vip) + "�������\n" NOR;
        msg += HIY "������ͨ��vip <id> <num>����ӹ��������num 1--9��ʾ1--9�ۣ�num 10��ʾȡ������ʸ�\n" NOR;
        return msg;
}

public string do_vip(object ob,object me,string arg)
{
        int num;

        if (!ob->query("shop_type"))
               return "�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n";

        if (!sscanf(arg,"%s %d",arg,num) == 2)
                return "ָ���ʽ��vip <id> <num>����ӹ��������num 1--9��ʾ1--9�ۣ�num 10��ʾȡ������ʸ�\n";

        if (num < 1 || num > 10)
                return "ָ���ʽ��vip <id> <num>����ӹ��������num 1--9��ʾ1--9�ۣ�num 10��ʾȡ������ʸ�\n";

        if (num == 10)
        {
                if (!ob->query("vip/" + arg))
                        return ob->name(1) + "��ֵĿ�����˵��" + arg + "�����Ͳ������ǵ�Ĺ������\n";
                ob->delete("vip/" + arg);
                ob->save();
                return ob->name(1) + "�����ʲ��ñʻ���һ�£�̧ͷ�������ļ�Ц�Ŷ���˵���ϰ壬���ǵ��Ѿ��ɹ�ȡ����" + arg + "�Ĺ���ʸ�\n";
        }
        ob->set("vip/" + arg,num);
        ob->save();
        return ob->name(1) + "�����ʲ�д�˵㶫����̧ͷ����˵���ϰ壬���ǵ����ڿ�ʼ��" + arg + "ʵ��" + HIY + chinese_number(num) + "��" + NOR + "�Żݣ�\n";
}

public string list_unwelcome(object ob,object me)
{
        int i;
        string msg,*unwelcome;

        if (!ob->query("shop_type"))
               return "�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n";

        unwelcome = ob->query("unwelcome");
        if (!unwelcome || sizeof(unwelcome) < 1)
        {
                msg = "����û�ж����κεĺڻ���\n";
                msg += "������ͨ��unwelcome <id>����Ӻڻ���Ҳ����ͨ��unwelcome <id> -clear��ȡ��ָ���ڻ���\n";
                return msg;
        }
        msg = HIY "��������ĺڻ���������ң�\n" NOR;
        msg += "------------------------------\n";
        for (i = 0;i < sizeof(unwelcome);i++)
        {
                msg += sprintf(HIW "%s\n" NOR, unwelcome[i]);
        }
        msg += "------------------------------\n";
        msg += HIY "�ܹ�" + sizeof(unwelcome) + "���ڻ���\n" NOR;
        msg += HIY "������ͨ��unwelcome <id>����Ӻڻ���Ҳ����ͨ��unwelcome <id> -clear��ȡ��ָ���ڻ���\n" NOR;
        
        return msg;
}

public string do_unwelcome(object ob,object me,string arg)
{
        string the_id,type,*unwelcome;

        if (!ob->query("shop_type"))
               return "�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n";
        
        unwelcome = ob->query("unwelcome");
        if (!unwelcome) unwelcome = ({});

        if (sscanf(arg,"%s %s",the_id,type) == 2 && type == "-clear")
        {
                if (member_array(the_id,unwelcome) == -1)
                        return ob->name(1) + "��ֵĿ�����˵��" + the_id + "���������ǵĺڻ���!\n";
                unwelcome -= ({ the_id });
                ob->set("unwelcome",unwelcome);
                ob->save();
                return ob->name(1) + "�����ʲ��ñʻ���һ�£�̧ͷ�Ǻ�Ц�Ŷ���˵���ϰ壬���ǵ��Ѿ��ɹ�ȡ����" + the_id + "�ĺڻ���ݡ�\n";
        }
        
        if (member_array(arg,unwelcome) != -1)
                return ob->name(1) + "��Ц�Ŷ���˵���ϰ壬�������ˣ�" + arg + "���Ѿ������ǵĺڻ���!\n";

        unwelcome += ({ arg });
        ob->set("unwelcome",unwelcome);
        ob->save();
        return ob->name(1) + "�����ʲ�д�˵㶫����̧ͷ����˵���ϰ壬���ǵ����ڿ�ʼ��" + arg + "��Ϊ�ڻ�����\n";
}

private void destruct_it(object ob)
{
        if (! ob || environment(ob))
                return;
        destruct(ob);
}

public int do_short(object me,string arg)
{
    string prop, str;
    mixed data;

    if (!environment(me)->query("shop_type"))
    {
        tell_object(me,"�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n");
        return 1;
    }

    if( !arg )
    {
        tell_object(me,"ָ���ʽ��short <�ڵ�����>\n");
        return 1;
    }

    tell_object(me,"���úڵ�����Ϊ��"+arg);
    environment(me)->set("short", arg);
    tell_object(me,"...Ok.\n");
    do_saveroom(me);
    return 1;
}

public int do_long(object me)
{
    string arg;
    arg="";

    if (!environment(me)->query("shop_type"))
    {
        tell_object(me,"�Բ��𣬸úڵ�Ŀǰ�Ѿ�����ʦ�رգ�\n");
        return 1;
    }

    tell_object(me,"ѶϢ�����кü��У������� . ��ʾ������\n");
    tell_object(me,"------------------------------------\n");
    input_to("get_long",arg,me);
    return 1;
}

private int get_long(string msg,string arg,object me)
{
    if( msg=="."){
        environment(me)->set("long", arg);
        tell_object(me,"Ok.\n");
        do_saveroom(me);
        return 1;
    }
    arg+=msg+"\n";
    input_to("get_long",arg,me);
    return 1;
}

private varargs int do_saveroom(object me,object the_room)
{
    object env;
    string str, *name, file;
    mapping prop;
    int i;
    if (the_room) 
            env = the_room;
    else
            env = environment(me);
    file = file_name(env) + ".c";
    str = "// �ڵ�: " + file +@ROOM_CODE

// �ڵ������smallfish��д

inherit ROOM;
inherit F_HEIDIAN;

void create()
{
ROOM_CODE
;
    str += sprintf("\tset(\"short\", %O);\n", env->query("short") );
    str += sprintf("\tset(\"long\", @LONG\n%sLONG\n);\n", env->query("long") );
    str += "\n\tset(\"no_fight\",1);\n";
    prop = env->query_entire_dbase();
    name = keys(prop);
    for(i=0; i<sizeof(name); i++) {
        if( member_array(name[i], special_props)!=-1 ) continue;
        str += sprintf("\tset(\"%s\", %O);\n", name[i], prop[name[i]] );
    }
    str += "\n\tsetup();\n}\n";
    // Replace current directory with __DIR__ macro to make relocatable code.
    i = strlen(file)-1;
    while( (i > 0) && (file[i]!='/')) i--;
    if( i>0 ) {
        str = replace_string(str, "\"" + file[0..i], "__DIR__\"");
    }
    str += @ROOM_CODE
 
init()
{
    if (query("owner") == this_player()->query("id"))
    {
        add_action("do_short","short");
        add_action("do_long","long");
    }
}
ROOM_CODE
;
    return save_room_file("y", file, str,me);
}

private int save_room_file(string yn, string file, string str, object me)
{
    if( strlen(yn)<1 || yn[0]!='y' ) return 1;
    seteuid(ROOT_UID);
    rm(file);
    tell_object(me,"�浵 " + file + "....");
    if( write_file(file, str) ) {
        tell_object(me,"Ok.\n");
        return update(me,file);
    } else
    {
        tell_object(me,"��û��д���������(" + file + ")��Ȩ����\n");
        return 1;
    }
}

private int update(object me, string file)
{
        int i;
        object obj, *inv;
        string err;

        seteuid( geteuid(me) );

        if( !sscanf(file, "%*s.c") ) file += ".c"; 

        if( file_size(file)==-1 )
        {
                tell_object(me,"�ڵ굵����������ϵ��ʦ��\n");
                return 0;
        }

        if (obj = find_object(file)) {
                if( obj==environment(me) ) {
                        if( file_name(obj)==VOID_OB )
                        {
                                tell_object(me,"�㲻���� VOID_OB�����±��� VOID_OB��\n");
                                return 0;
                        }
                        inv = all_inventory(obj);
                        i = sizeof(inv);
                        while(i--)
                                if( userp(inv[i]) ) inv[i]->move(VOID_OB, 1);
                                else inv[i] = 0;
                }
                destruct(obj);
        }

        if (obj) 
        {
                tell_object(me,"�޷�����ɳ�ʽ�롣\n");
                return 0;
        }

        tell_object(me,"���±��� " + file + "��");
        err = catch( call_other(file, "???") );
        if (err)
                tell_object(me,sprintf("��������\n%s\n", err) );
        else {
                tell_object(me,"�ɹ���\n");
                if( (i=sizeof(inv)) && (obj = find_object(file))) {
                        while(i--)
                                if( inv[i] && userp(inv[i])) 
                                        inv[i]->move(obj, 1);
                }
        }
        return 1;
}
