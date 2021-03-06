// 为特殊道具开光

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
                return notify_fail("你要为什么物品开光？\n");

        if (! objectp(ob = present(str, me)))
                return notify_fail("你身上没有这个物品。\n");

        if (! ob->query("can_summon"))
                return notify_fail("这个物品不能开光。\n");

        if (stringp(me->query("can_summon/" + str)))
                return notify_fail("这个物品已经开过光了。\n");

        ob->set("owner_id", me->query("id"));
        ob->set("owner_name", me->name());

        if (me->query("max_qi") < 3000 ||
            me->query("qi") != me->query("max_qi"))
                return notify_fail("你气血不足，无法开光。\n");

        if (me->query("max_jingli") < 1000 ||
            me->query("jingli") != me->query("max_jingli"))
                return notify_fail("你精力不足，无法开光。\n");

        if (me->query("max_neili") < 3000 ||
            me->query("neili") != me->query("max_neili"))
                return notify_fail("你内力不足，无法开光。\n");

        if (! me->query_temp("want_kaiguang"))
        {
                me->set_temp("want_kaiguang", 1);
                write(HIC "为" + ob->name() + HIC "开光需要消耗你的气"
                      "血、内力、精力的最大值，如果决定了请再输入一次该指令。\n");

                return 1;
        }

        me->start_busy(4 + random(4));
        message_sort(HIR "\n$N" HIR "用利刃将双手手心划破，双掌贴在" + ob->name() + HIR "上，"
                     "渐渐地，" + ob->name() + HIR "将$N" HIR "的鲜血吸收……\n\n" NOR, me);
 
        if (item_filename = create_file(ob))
        {

                destruct(ob);
                catch(call_other(item_filename, "???"));
                ob = find_object(item_filename);
                if (! ob)
                {
                        write("文件出错，请与巫师联系！\n");
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

                        tell_object(me, NOR + RED "你感觉你的：\n\t\t精力下降了，\n\t\t内力下"
                                        "降了，\n\t\t气血下降了！\n\n" NOR);
                        
                        tell_object(me, HIG "开光成功！以后请用 summon " + 
                                    ob->query("summon_id") + " 来召唤该物品。\n" NOR);
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
        string  buf;                    // 生成文件的缓冲区
        string  filename;
        string  desc;
        string id;

        // 生成文件名
        id = item_temp->query("owner_id");
        filename = ITEM_DIR + id[0..0] + "/" + id + 
                   "-SPECIAL-" + item_temp->query("summon_id") + ".c";

        if (file_size(filename) != -1)
        {
                write("无法生成档案，请通知巫师处理。\n");
                return 0;
        }

        assure_file(filename);
        buf = "// ITEM Made by player(" + item_temp->query("owner_name") +
              ":" + item_temp->query("owner_id") + ") " + filename + 
              "\n// Written by yuchang@zhyx\t" + ctime(time()) + "\n";

        if (1) // 扩展
        {
                // 生成防护道具文件
                desc = "这是由" + item_temp->query("material_name") + "炼制而成的一" +
                       item_temp->query("unit") + item_temp->query("ctype") + "。\n";

                desc += item_temp->query("long");
                if (desc[strlen(desc) - 1] != '\n')
                        desc += "\n";

                desc += item_temp->query("ctype") + "缘上刻着一行小字：" +
                        item_temp->query("owner_name") + "(" + item_temp->query("owner_id") + ")\n";

                // 自动补充空信息
                if (! stringp(item_temp->query("summon_wear_msg")))
                        item_temp->set("summon_wear_msg", YEL "$N" YEL "装备" +
                                       item_temp->name() + YEL "。" NOR);
                if (! stringp(item_temp->query("summon_remove_msg")))
                        item_temp->set("summon_remove_msg", YEL "$N" YEL "脱下了" +
                                        item_temp->name() + YEL "。" NOR);
                
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
                // 生成防护道具文件完毕
        }
        buf += sprintf("int query_autoload() { return 1;}\n\n");
        buf += sprintf("void autoload(string parameter) {this_object()->wear();}\n\n");
        //buf += sprintf("public int receive_summon(object me)\n{\n\treturn ITEM_D->receive_summon(me, this_object());\n}\n");

        if (save_item_file(filename, buf) == 1)
                return filename;

        return 0;
}

// filename 是写入文档的名称，已经包含有路径
// content 是写入文档的内容
private int save_item_file(string filename, string content)
{
        rm(filename);
        if (write_file(filename, content))
        {
                VERSION_D->append_sn(filename);
                return 1;
        } else
        {
                write("写入档案(" + filename + ")时出错，请通知巫师处理。\n");
                return 0;
        }
}

int help(object me)
{
write(@HELP
指令格式 : kaiguang <物品的ID>

为特殊道具开光，开光后可以召唤该道具。
HELP);
    return 1;
}

