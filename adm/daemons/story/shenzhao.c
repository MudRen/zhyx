// story:shenzhao 凝血神爪

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string family_name;
mixed give_gift1();
int   give_gift2();

object select_character();

nosave mixed *story = ({
        "只听那黑衣大汉大笑道：“顾炎武，黄宗羲，吕留良，看你们今天往哪里逃？给我拿下了！”",
        "四名亲兵立即应道：“是，谨遵瓜管带吩咐。”",
        "瓜管带道：“回京后见了鳌少保，人人不愁生官发财。”",
        "一名亲兵笑道：“那都是瓜管带提拔栽培，单凭我们四个，那有这等福分？”",
        "船头忽然有人嘿嘿一笑，说道：“凭你们四人，原也没这等福分。”",
        "船舱门呼的一声，向两旁飞开，只见一人负手背后，脸露微笑。",
        "瓜管带道：“官老爷们在这里办案，你是谁？”",
        "那人微笑不答，迈步踏进船舱。顿时刀光闪动，四柄单刀分从四方劈落。",
        "那人手起手落，连出四掌，分别拍在四名亲兵的胸口，咯咯声响，四人肋骨齐断。",
        "瓜管带见势不妙，连忙纵身一跃，从船舱缺口中跳了出去。",
        "那人奔到船头，正欲追赶，却见一书生提起竹篙，挥手掷出。",
        "竹篙犹似飞蛇，急射而前。但听瓜管带“啊“的一声，斥革已插入他后心，将他钉在地上。",
        "两人奔上岸边，见瓜管带已经死得透了，这才相互报以一笑。",
        "那人和那书生心中都暗自称奇，心想：“这人是谁，武功如此之高，当真世所罕有。”",
        "两人走进船舱，解开顾黄吕三人的穴道，又将四名亲兵的尸体抛入运河，重点灯烛。",
        "顾黄吕三人不住道谢，问起两人姓名。",
        "那书生道：“贱名适才承蒙黄先生齿及，在下姓陈，草字近南。敢问这位英雄大名？”",
        "那人却道：“英雄不问出处，举手之劳，何足挂齿？他日与陈总舵主江湖相逢，定当把酒言欢。”说完便飘然而去。",
        "陈近南道：“果真是人中豪杰，只可惜尚不知道此人姓名，唉...”说完长长的叹了口气。",
        (: give_gift1 :),
        "陈近南拱了拱手，道：“这位英雄，今日得以见识阁下武艺之高超，品德之高尚，你我既有缘，何不留下姓名？”",
        "那人微笑道：“无威无德，岂当‘英雄’二字，在下$F$N，承蒙陈总舵主见笑了。”",
        "陈近南道：“阁下武功高强，但阁下侠义热血更为可贵，今日和阁下携手一战，畅快无比。”",
        "$N笑道：“陈总舵主名满天下，今日一见，武功果然了得！”",
        "陈近南微笑道：“看阁下是武林中人，今日便赠予阁下一幅苍鹰搏兔图作为信物，他日如有事需要在下帮忙，可凭此画到北京城来找我。”",
        (: give_gift2 :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_character()))
        {
                destruct(this_object());
                return;
        }
}

string prompt() { return HIC "【江湖奇遇】" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: ultrap($1) &&
                              living($1) &&
                              $1->query("combat_exp") >= 5000000 &&
                              $1->query_skill("unarmed", 1) > 300 &&
                              $1->query_skill("ningxue-shenzhao", 1) < 1 &&
                              $1->query("family/family_name") &&
                              $1->query_dex() > 45 &&
                              $1->query("str") > 38 &&
                              $1->query("shen") > 0 &&
                              ! $1->query("story/shenzhao") &&
                              ! wizardp($1) &&
                              ! $1->query("doing") :));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        char_id = ob->query("id");
        char_name = ob->name(1);
        family_name = ob->query("family/family_name");
        return ob;
}

mixed query_story_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg, "$N", char_name);
                msg = replace_string(msg, "$F", family_name);
                msg = replace_string(msg, "$ID", char_id);
        }
        return msg;
}

mixed give_gift1()
{
        object ob;
        ob = find_player(char_id);
	if (ob->query("story/shenzhao") || random( 550 - ob->query("kar") * 10 ) > 1 )
        {
	        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + ob->name(1) +
                              "与陈近南一同力战众敌，两人之间留下了深刻的友谊。");
                return 0;
        }
        return "陈近南心想：此人与我颇为有缘，如此走了岂不可惜？随后飞奔追上那人。";
}

int give_gift2()
{
        object ob;
        object book;

        ob = find_player(char_id);
        if (! ob) return 1;

        /* if (ob->query_skill("ningxue-shenzhao", 1) < 10)
                ob->set_skill("ningxue-shenzhao", 10); */

        ob->set("story/shenzhao", 1);
        tell_object(ob, HIC "你得到了苍鹰搏兔图。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "听说陈近南将随身携带的苍鹰搏兔图作为信物赠与了" + ob->name(1) +
                              "。");
        book = new("/u/dgdg/obj/cangying-hua");
        book->move(ob, 1);
        return 1;
}
