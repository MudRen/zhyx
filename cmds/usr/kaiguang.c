// Ϊ������߿���

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;
string create_file(object item_temp);
int save_item_file(string filename, string content);

int main(object me, string str)
{
	object ob;
        string item_filename;

	if (! str)
                return notify_fail("��ҪΪʲô��Ʒ���⣿\n");

        if (! objectp(ob = present(str, me)))
                return notify_fail("������û�������Ʒ��\n");

        if (! ob->query("can_summon"))
                return notify_fail("�����Ʒ���ܿ��⡣\n");

        if (stringp(me->query("can_summon/" + str)))
                return notify_fail("�����Ʒ�Ѿ��������ˡ�\n");

        ob->set("owner_id", me->query("id"));
        ob->set("owner_name", me->name());

        if (me->query("max_qi") < 3000 ||
            me->query("qi") != me->query("max_qi"))
                return notify_fail("����Ѫ���㣬�޷����⡣\n");

        if (me->query("max_jingli") < 1000 ||
            me->query("jingli") != me->query("max_jingli"))
                return notify_fail("�㾫�����㣬�޷����⡣\n");

        if (me->query("max_neili") < 3000 ||
            me->query("neili") != me->query("max_neili"))
                return notify_fail("���������㣬�޷����⡣\n");

        if (! me->query_temp("want_kaiguang"))
        {
                me->set_temp("want_kaiguang", 1);
                write(HIC "Ϊ" + ob->name() + HIC "������Ҫ���������"
                      "Ѫ�����������������ֵ�������������������һ�θ�ָ�\n");

                return 1;
        }

        me->start_busy(4 + random(4));
        message_sort(HIR "\n$N" HIR "�����н�˫�����Ļ��ƣ�˫������" + ob->name() + HIR "�ϣ�"
                     "�����أ�" + ob->name() + HIR "��$N" HIR "����Ѫ���ա���\n\n" NOR, me);
 
	if (item_filename = create_file(ob))
	{

		destruct(ob);
                catch(call_other(item_filename, "???"));
		ob = find_object(item_filename);
                if (! ob)
                {
                        write("�ļ�����������ʦ��ϵ��\n");
                        log_file("static/kaiguang_error", sprintf("%s %s creating  %s(%s) had errors.\n",
				 log_time(), log_id(me), filter_color(ob->name(1)), ob->query("id")));
                        return 1;
                } else
                {
		        ob->move(me, 1);
                        ob->save();             // Create the record in dbase

                        me->add("max_neili", -400);
                        me->add("neili", -600);
                        me->add("max_jingli", -200);
                        me->add("jingli", -400);
                        me->add("max_qi", -400);
                        me->add("qi", -600);
                        
		        message_sort(ob->query("wear_msg"), me);

                        tell_object(me, NOR + RED "��о���ģ�\n\t\t�����½��ˣ�\n\t\t������"
                                        "���ˣ�\n\t\t��Ѫ�½��ˣ�\n\n" NOR);
                        
                        tell_object(me, HIG "����ɹ����Ժ����� summon " + 
                                    ob->query("summon_id") + " ���ٻ�����Ʒ��\n" NOR);
                        log_file("static/kaiguang", sprintf("%s %s created  %s(%s)\n",
				 log_time(), log_id(me),
                                 filter_color(ob->name(1)), ob->query("id")));
                }
                me->set("can_summon/" + ob->query("summon_id"), item_filename);
                me->save();
                if (me->query_temp("want_kaiguang"))
                        me->delete_temp("want_kaiguang");
	}
        
        return 1;
	
}

string create_file(object item_temp)
{
	string	buf;			// �����ļ��Ļ�����
	string	filename;
        string  desc;
        string id;

	// �����ļ���
        id = item_temp->query("owner_id");
	filename = ITEM_DIR + id[0..0] + "/" + id + 
		   "-SPECIAL-" + item_temp->query("summon_id") + ".c";

	if (file_size(filename) != -1)
	{
		write("�޷����ɵ�������֪ͨ��ʦ����\n");
		return 0;
	}

        assure_file(filename);
	buf = "// ITEM Made by player(" + item_temp->query("owner_name") +
              ":" + item_temp->query("owner_id") + ") " + filename + 
	      "\n// Written by Rcwiz(Tokza Yo 2003/4/17)\t" + ctime(time()) + "\n";

	if (1) // ��չ
        {
		// ���ɷ��������ļ�
		desc = "������" + item_temp->query("material_name") + "���ƶ��ɵ�һ" +
		       item_temp->query("unit") + item_temp->query("ctype") + "��\n";

                desc += item_temp->query("long");
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

		desc += item_temp->query("ctype") + "Ե�Ͽ���һ��С�֣�" +
		        item_temp->query("owner_name") + "(" + item_temp->query("owner_id") + ")\n";

		// �Զ��������Ϣ
                if (! stringp(item_temp->query("summon_wear_msg")))
               	        item_temp->set("summon_wear_msg", YEL "$N" YEL "װ��" +
                                       item_temp->name() + YEL "��" NOR);
                if (! stringp(item_temp->query("summon_remove_msg")))
        		item_temp->set("summon_remove_msg", YEL "$N" YEL "������" +
	            			item_temp->name() + YEL "��" NOR);
                
		buf += "#include <ansi.h>\n";
		buf += "#include <armor.h>\n\n";
		buf += "inherit ARMOR;\ninherit F_ITEMMAKE;\n";
                buf += "void create()\n{\n";

		buf += sprintf("\tset_name(\"%s\", ({ \"%s\" }));\n", 
				item_temp->name(), item_temp->query("summon_id"));
		buf += sprintf("\tset_weight(%d);\n", item_temp->query_weight());

                buf += sprintf("\tif (clonep())set_default_object(__FILE__);\n");
                buf += sprintf("\telse {\n");

                buf += sprintf("\t\tset(\"owner_name\", \"%s\");\n", item_temp->query("owner_name"));
                buf += sprintf("\t\tset(\"owner_id\", \"%s\");\n", item_temp->query("owner_id"));
                buf += sprintf("\t\tset(\"summon_id\", \"%s\");\n", item_temp->query("summon_id"));
		buf += sprintf("\t\tset(\"unit\", \"%s\");\n", item_temp->query("unit"));
		buf += sprintf("\t\tset(\"long\", \"%s\");\n", desc);
		buf += sprintf("\t\tset(\"value\", %d);\n", item_temp->query("value"));
		buf += sprintf("\t\tset(\"material\", \"%s\");\n", item_temp->query("material"));
		buf += sprintf("\t\tset(\"wear_msg\", \"%s\\n\");\n", item_temp->query("summon_wear_msg"));
		buf += sprintf("\t\tset(\"remove_msg\", \"%s\\n\");\n", item_temp->query("summon_remove_msg"));

                buf += sprintf("\t\tset(\"armor_prop/armor\", %d);\n", item_temp->query("armor_prop/armor"));
                buf += sprintf("\t\tset(\"armor_prop/dodge\", %d);\n", item_temp->query("armor_prop/dodge"));
                buf += sprintf("\t\tset(\"armor_prop/parry\", %d);\n", item_temp->query("armor_prop/parry"));
                buf += sprintf("\t\tset(\"armor_prop/reduce_poison\", %d);\n", item_temp->query("armor_prop/reduce_poison"));
                buf += sprintf("\t\tset(\"armor_prop/avoid_poison\", %d);\n", item_temp->query("armor_prop/avoid_poison"));
                buf += sprintf("\t\tset(\"reduce_msg\", \"%s\\n\");\n", item_temp->query("reduce_msg"));
                buf += sprintf("\t\tset(\"avoid_msg\", \"%s\\n\");\n", item_temp->query("avoid_msg"));

                buf += sprintf("\t}\n");

		buf += sprintf("\n\tsetup();\n}\n\n");
		// ���ɷ��������ļ����
	}
        buf += sprintf("int query_autoload() { return 1;}\n\n");
        buf += sprintf("void autoload(string parameter) {this_object()->wear();}\n\n");
        //buf += sprintf("public int receive_summon(object me)\n{\n\treturn ITEM_D->receive_summon(me, this_object());\n}\n");

	if (save_item_file(filename, buf) == 1)
		return filename;

	return 0;
}

// filename ��д���ĵ������ƣ��Ѿ�������·��
// content ��д���ĵ�������
private int save_item_file(string filename, string content)
{
	rm(filename);
	if (write_file(filename, content))
	{
                VERSION_D->append_sn(filename);
		return 1;
	} else
	{
		write("д�뵵��(" + filename + ")ʱ������֪ͨ��ʦ����\n");
		return 0;
	}
}

int help(object me)
{
write(@HELP
ָ���ʽ : kaiguang <��Ʒ��ID>

Ϊ������߿��⣬���������ٻ��õ��ߡ�
HELP);
    return 1;
}
