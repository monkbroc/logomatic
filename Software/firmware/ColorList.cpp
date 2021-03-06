#include "ColorList.h"
#include "utils.h"
#include "string.h"

struct {
    const char *name;
    const char *hex;
} colorNames[] = {
"particle blue",	   "#00adef",
    // HTML colors
"tan",	   "#d2b48c",
"red",	   "#ff0000",
"teal",	   "#008080",
"snow",	   "#fffafa",
"plum",	   "#dda0dd",
"pink",	   "#ffc0cb",
"peru",	   "#cd853f",
"navy",	   "#000080",
"lime",	   "#00ff00",
"grey",	   "#808080",
"gray",	   "#808080",
"gold",	   "#ffd700",
"cyan",	   "#00ffff",
"blue",	   "#0000ff",
"white",	   "#ffffff",
"wheat",	   "#f5deb3",
"aqua",	   "#00ffff",
"olive",	   "#808000",
"linen",	   "#faf0e6",
"khaki",	   "#f0e68c",
"ivory",	   "#fffff0",
"green",	   "#00ff00",
"coral",	   "#ff7f50",
"brown",	   "#a52a2a",
"black",	   "#000000",
"beige",	   "#f5f5dc",
"azure",	   "#f0ffff",
"yellow",	   "#ffff00",
"violet",	   "#ee82ee",
"tomato",	   "#ff6347",
"silver",	   "#c0c0c0",
"sienna",	   "#a0522d",
"salmon",	   "#fa8072",
"purple",	   "#800080",
"orchid",	   "#da70d6",
"orange",	   "#ffa500",
"maroon",	   "#800000",
"indigo",	   "#4b0082",
"bisque",	   "#ffe4c4",
"thistle",	   "#d8bfd8",
"sky blue",	   "#87ceeb",
"old lace",	   "#fdf5e6",
"magenta",	   "#ff00ff",
"hot pink",	   "#ff69b4",
"fuchsia",	   "#ff00ff",
"dim grey",	   "#696969",
"dim gray",	   "#696969",
"dark red",	   "#8b0000",
"crimson",	   "#dc143c",
"sea shell",	   "#fff5ee",
"sea green",	   "#2e8b57",
"moccasin",	   "#ffe4b5",
"lavender",	   "#e6e6fa",
"honey dew",	   "#f0fff0",
"deep pink",	   "#ff1493",
"dark grey",	   "#a9a9a9",
"dark gray",	   "#a9a9a9",
"dark cyan",	   "#008b8b",
"dark blue",	   "#00008b",
"cornsilk",	   "#fff8dc",
"turquoise",	   "#40e0d0",
"steel blue",	   "#4682b4",
"slate grey",	   "#708090",
"slate gray",	   "#708090",
"slate blue",	   "#6a5acd",
"royal blue",	   "#4169e1",
"rosy brown",	   "#bc8f8f",
"peach puff",	   "#ffdab9",
"pale green",	   "#98fb98",
"orange red",	   "#ff4500",
"olive drab",	   "#6b8e23",
"misty rose",	   "#ffe4e1",
"mint cream",	   "#f5fffa",
"lime green",	   "#32cd32",
"light pink",	   "#ffb6c1",
"light grey",	   "#d3d3d3",
"light gray",	   "#d3d3d3",
"light cyan",	   "#e0ffff",
"light blue",	   "#add8e6",
"lawn green",	   "#7cfc00",
"indian red",	   "#cd5c5c",
"golden rod",	   "#daa520",
"gainsboro",	   "#dcdcdc",
"fire brick",	   "#b22222",
"dark khaki",	   "#bdb76b",
"dark green",	   "#006400",
"chocolate",	   "#d2691e",
"cadet blue",	   "#5f9ea0",
"burly wood",	   "#deb887",
"white smoke",	   "#f5f5f5",
"sandy brown",	   "#f4a460",
"powder blue",	   "#b0e0e6",
"papaya whip",	   "#ffefd5",
"medium blue",	   "#0000cd",
"light green",	   "#90ee90",
"light coral",	   "#f08080",
"alice blue",	   "#f0f8ff",
"ghost white",	   "#f8f8ff",
"dodger blue",	   "#1e90ff",
"dark violet",	   "#9400d3",
"dark salmon",	   "#e9967a",
"dark orchid",	   "#9932cc",
"dark orange",	   "#ff8c00",
"chartreuse",	   "#7fff00",
"blue violet",	   "#8a2be2",
"yellow green",	   "#9acd32",
"spring green",	   "#00ff7f",
"saddle brown",	   "#8b4513",
"aquamarine",	   "#7fffd4",
"navajo white",	   "#ffdead",
"light yellow",	   "#ffffe0",
"light salmon",	   "#ffa07a",
"green yellow",	   "#adff2f",
"forest green",	   "#228b22",
"floral white",	   "#fffaf0",
"deep sky blue",	   "#00bfff",
"dark magenta",	   "#8b008b",
"midnight blue",	   "#191970",
"medium purple",	   "#9370db",
"medium orchid",	   "#ba55d3",
"light sky blue",	   "#87cefa",
"lemon chiffon",	   "#fffacd",
"dark sea green",	   "#8fbc8f",
"rebecca purple",	   "#663399",
"pale violet red",	   "#db7093",
"pale turquoise",	   "#afeeee",
"pale golden rod",	   "#eee8aa",
"antique white",	   "#faebd7",
"light sea green",	   "#20b2aa",
"lavender blush",	   "#fff0f5",
"dark turquoise",	   "#00ced1",
"dark slate grey",	   "#2f4f4f",
"dark slate gray",	   "#2f4f4f",
"dark slate blue",	   "#483d8b",
"dark golden rod",	   "#b8860b",
"medium sea green",	   "#3cb371",
"light steel blue",	   "#b0c4de",
"light slate grey",	   "#778899",
"light slate gray",	   "#778899",
"dark olive green",	   "#556b2f",
"cornflower blue",	   "#6495ed",
"blanched almond",	   "#ffebcd",
"medium violet red",	   "#c71585",
"medium turquoise",	   "#48d1cc",
"medium slate blue",	   "#7b68ee",
"medium aqua marine",	   "#66cdaa",
"medium spring green",	   "#00fa9a",
"light golden rod yellow",	   "#fafad2",

    // Crayola colors
"red",                           "#ED0A3F",
"maroon",                        "#C32148",
"scarlet",                       "#FD0E35",
"brick red",                     "#C62D42",
"english vermilion",             "#CC474B",
"madder lake",                   "#CC3336",
"permanent geranium lake",       "#E12C2C",
"maximum red",                   "#D92121",
"indian red",                    "#B94E48",
"orange-red",                    "#FF5349",
"sunset orange",                 "#FE4C40",
"bittersweet",                   "#FE6F5E",
"dark venetian red",             "#B33B24",
"venetian red",                  "#CC553D",
"light venetian red",            "#E6735C",
"vivid tangerine",               "#FF9980",
"middle red",                    "#E58E73",
"burnt orange",                  "#FF7F49",
"red-orange",                    "#FF681F",
"orange",                        "#FF8833",
"macaroni and cheese",           "#FFB97B",
"middle yellow red",             "#ECAC76",
"mango tango",                   "#E77200",
"yellow-orange",                 "#FFAE42",
"maximum yellow red",            "#F2BA49",
"banana mania",                  "#FBE7B2",
"maize",                         "#F2C649",
"orange-yellow",                 "#F8D568",
"goldenrod",                     "#FCD667",
"dandelion",                     "#FED85D",
"yellow",                        "#FBE870",
"green-yellow",                  "#F1E788",
"middle yellow",                 "#FFEB00",
"olive green",                   "#B5B35C",
"spring green",                  "#ECEBBD",
"maximum yellow",                "#FAFA37",
"canary",                        "#FFFF99",
"lemon yellow",                  "#FFFF9F",
"maximum green yellow",          "#D9E650",
"middle green yellow",           "#ACBF60",
"inchworm",                      "#AFE313",
"light chrome green",            "#BEE64B",
"yellow-green",                  "#C5E17A",
"maximum green",                 "#5E8C31",
"asparagus",                     "#7BA05B",
"granny smith apple",            "#9DE093",
"fern",                          "#63B76C",
"middle green",                  "#4D8C57",
"green",                         "#3AA655",
"medium chrome green",           "#6CA67C",
"forest green",                  "#5FA777",
"sea green",                     "#93DFB8",
"shamrock",                      "#33CC99",
"mountain meadow",               "#1AB385",
"jungle green",                  "#29AB87",
"caribbean green",               "#00CC99",
"tropical rain forest",          "#00755E",
"middle blue green",             "#8DD9CC",
"pine green",                    "#01786F",
"maximum blue green",            "#30BFBF",
"robin's egg blue",              "#00CCCC",
"teal blue",                     "#008080",
"light blue",                    "#8FD8D8",
"aquamarine",                    "#95E0E8",
"turquoise blue",                "#6CDAE7",
"outer space",                   "#2D383A",
"sky blue",                      "#76D7EA",
"middle blue",                   "#7ED4E6",
"blue-green",                    "#0095B7",
"pacific blue",                  "#009DC4",
"cerulean",                      "#02A4D3",
"maximum blue",                  "#47ABCC",
"blue (i)",                      "#2EB4E6",
"cerulean blue",                 "#339ACC",
"cornflower",                    "#93CCEA",
"green-blue",                    "#2887C8",
"midnight blue",                 "#00468C",
"navy blue",                     "#0066CC",
"denim",                         "#1560BD",
"blue (iii)",                    "#0066FF",
"cadet blue",                    "#A9B2C3",
"periwinkle",                    "#C3CDE6",
"blue (ii)",                     "#4570E6",
"wild blue yonder",              "#7A89B8",
"indigo",                        "#4F69C6",
"manatee",                       "#8D90A1",
"cobalt blue",                   "#8C90C8",
"celestial blue",                "#7070CC",
"blue bell",                     "#9999CC",
"maximum blue purple",           "#ACACE6",
"violet-blue",                   "#766EC8",
"blue-violet",                   "#6456B7",
"ultramarine blue",              "#3F26BF",
"middle blue purple",            "#8B72BE",
"purple heart",                  "#652DC1",
"royal purple",                  "#6B3FA0",
"violet (ii)",                   "#8359A3",
"medium violet",                 "#8F47B3",
"wisteria",                      "#C9A0DC",
"lavender (i)",                  "#BF8FCC",
"vivid violet",                  "#803790",
"maximum purple",                "#733380",
"purple mountains' majesty",     "#D6AEDD",
"fuchsia",                       "#C154C1",
"pink flamingo",                 "#FC74FD",
"violet (i)",                    "#732E6C",
"brilliant rose",                "#E667CE",
"orchid",                        "#E29CD2",
"plum",                          "#8E3179",
"medium rose",                   "#D96CBE",
"thistle",                       "#EBB0D7",
"mulberry",                      "#C8509B",
"red-violet",                    "#BB3385",
"middle purple",                 "#D982B5",
"maximum red purple",            "#A63A79",
"jazzberry jam",                 "#A50B5E",
"eggplant",                      "#614051",
"magenta",                       "#F653A6",
"cerise",                        "#DA3287",
"wild strawberry",               "#FF3399",
"lavender (ii)",                 "#FBAED2",
"cotton candy",                  "#FFB7D5",
"carnation pink",                "#FFA6C9",
"violet-red",                    "#F7468A",
"razzmatazz",                    "#E30B5C",
"pig pink",                      "#FDD7E4",
"carmine",                       "#E62E6B",
"blush",                         "#DB5079",
"tickle me pink",                "#FC80A5",
"mauvelous",                     "#F091A9",
"salmon",                        "#FF91A4",
"middle red purple",             "#A55353",
"mahogany",                      "#CA3435",
"melon",                         "#FEBAAD",
"pink sherbert",                 "#F7A38E",
"burnt sienna",                  "#E97451",
"brown",                         "#AF593E",
"sepia",                         "#9E5B40",
"fuzzy wuzzy",                   "#87421F",
"beaver",                        "#926F5B",
"tumbleweed",                    "#DEA681",
"raw sienna",                    "#D27D46",
"van dyke brown",                "#664228",
"tan",                           "#D99A6C",
"desert sand",                   "#EDC9AF",
"peach",                         "#FFCBA4",
"burnt umber",                   "#805533",
"apricot",                       "#FDD5B1",
"almond",                        "#EED9C4",
"raw umber",                     "#665233",
"shadow",                        "#837050",
"raw sienna (i)",                "#E6BC5C",
"timberwolf",                    "#D9D6CF",
"gold (i)",                      "#92926E",
"gold (ii)",                     "#E6BE8A",
"silver",                        "#C9C0BB",
"copper",                        "#DA8A67",
"antique brass",                 "#C88A65",
"black",                         "#000000",
"charcoal gray",                 "#736A62",
"gray",                          "#8B8680",
"blue-gray",                     "#C8C8CD",
"radical red",                   "#FF355E",
"wild watermelon",               "#FD5B78",
"outrageous orange",             "#FF6037",
"atomic tangerine",              "#FF9966",
"neon carrot",                   "#FF9933",
"sunglow",                       "#FFCC33",
"laser lemon",                   "#FFFF66",
"unmellow yellow",               "#FFFF66",
"electric lime",                 "#CCFF00",
"screamin' green",               "#66FF66",
"magic mint",                    "#AAF0D1",
"blizzard blue",                 "#50BFE6",
"shocking pink",                 "#FF6EFF",
"razzle dazzle rose",            "#EE34D2",
"hot magenta",                   "#FF00CC",
"purple pizzazz",                "#FF00CC",
"sizzling red",                  "#FF3855",
"red salsa",                     "#FD3A4A",
"tart orange",                   "#FB4D46",
"orange soda",                   "#FA5B3D",
"bright yellow",                 "#FFAA1D",
"yellow sunshine",               "#FFF700",
"slimy green",                   "#299617",
"green lizard",                  "#A7F432",
"denim blue",                    "#2243B6",
"blue jeans",                    "#5DADEC",
"plump purple",                  "#5946B2",
"purple plum",                   "#9C51B6",
"sweet brown",                   "#A83731",
"brown sugar",                   "#AF6E4D",
"eerie black",                   "#1B1B1B",
"black shadows",                 "#BFAFB2",
"fiery rose",                    "#FF5470",
"sizzling sunrise",              "#FFDB00",
"heat wave",                     "#FF7A00",
"lemon glacier",                 "#FDFF00",
"spring frost",                  "#87FF2A",
"absolute zero",                 "#0048BA",
"winter sky",                    "#FF007C",
"frostbite",                     "#E936A7",
"alloy orange",                  "#c46210",
"b'dazzled blue",                "#2e5894",
"big dip o' ruby",               "#9c2542",
"bittersweet shimmer",           "#bf4f51",
"blast off bronze",              "#a57164",
"cyber grape",                   "#58427c",
"deep space sparkle",            "#4a646c",
"gold fusion",                   "#85754e",
"illuminating emerald",          "#319177",
"metallic seaweed",              "#0a7e8c",
"metallic sunburst",             "#9c7c38",
"razzmic berry",                 "#8d4e85",
"sheen green",                   "#8fd400",
"shimmering blush",              "#d98695",
"sonic silver",                  "#757575",
"steel blue",                    "#0081ab",
"aztec gold",                    "#C39953",
"burnished brown",               "#A17A74",
"cerulean frost",                "#6D9BC3",
"cinnamon satin",                "#CD607E",
"copper penny",                  "#AD6F69",
"cosmic cobalt",                 "#2E2D88",
"glossy grape",                  "#AB92B3",
"granite gray",                  "#676767",
"green sheen",                   "#6EAEA1",
"lilac luster",                  "#AE98AA",
"misty moss",                    "#BBB477",
"mystic maroon",                 "#AD4379",
"pearly purple",                 "#B768A2",
"pewter blue",                   "#8BA8B7",
"polished pine",                 "#5DA493",
"quick silver",                  "#A6A6A6",
"rose dust",                     "#9E5E6F",
"rusty red",                     "#DA2C43",
"shadow blue",                   "#778BA5",
"shiny shamrock",                "#5FA778",
"steel teal",                    "#5F8A8B",
"sugar plum",                    "#914E75",
"twilight lavender",             "#8A496B",
"wintergreen dream",             "#56887D",
"baby powder",                   "#FEFEFA",
"banana",                        "#FFD12A",
"blueberry",                     "#4F86F7",
"bubble gum",                    "#FFD3F8",
"cedar chest",                   "#C95A49",
"cherry",                        "#DA2647",
"chocolate",                     "#BD8260",
"coconut",                       "#FEFEFE",
"daffodil",                      "#FFFF31",
"dirt",                          "#9B7653",
"eucalyptus",                    "#44D7A8",
"fresh air",                     "#A6E7FF",
"grape",                         "#6F2DA8",
"jelly bean",                    "#DA614E",
"leather jacket",                "#253529",
"lemon",                         "#FFFF38",
"licorice",                      "#1A1110",
"lilac",                         "#DB91EF",
"lime",                          "#B2F302",
"lumber",                        "#FFE4CD",
"new car",                       "#214FC6",
"orange",                        "#FF8866",
"peach",                         "#FFD0B9",
"pine",                          "#45A27D",
"rose",                          "#FF5050",
"shampoo",                       "#FFCFF1",
"smoke",                         "#738276",
"soap",                          "#CEC8EF",
"strawberry",                    "#FC5A8D",
"tulip",                         "#FF878D",
"amethyst",                      "#64609A",
"citrine",                       "#933709",
"emerald",                       "#14A989",
"jade",                          "#469A84",
"jasper",                        "#D05340",
"lapis lazuli",                  "#436CB9",
"malachite",                     "#469496",
"moonstone",                     "#3AA8C1",
"onyx",                          "#353839",
"peridot",                       "#ABAD48",
"pink pearl",                    "#B07080",
"rose quartz",                   "#BD559C",
"ruby",                          "#AA4069",
"sapphire",                      "#2D5DA1",
"smokey topaz",                  "#832A0D",
"tiger's eye",                   "#B56917",
"alien armpit",                  "#84DE02",
"big foot feet",                 "#E88E5A",
"booger buster",                 "#DDE26A",
"dingy dungeon",                 "#C53151",
"gargoyle gas",                  "#FFDF46",
"giant's club",                  "#B05C52",
"magic potion",                  "#FF4466",
"mummy's tomb",                  "#828E84",
"ogre odor",                     "#FD5240",
"pixie powder",                  "#391285",
"princess perfume",              "#FF85CF",
"sasquatch socks",               "#FF4681",
"sea serpent",                   "#4BC7CF",
"smashed pumpkin",               "#FF6D3A",
"sunburnt cyclops",              "#FF404C",
"winter wizard",                 "#A0E6FF",
};

Color colorFromName(String name) {
    if (name.length() == 0) {
        return ParticleBlue;
    }

    name.toLowerCase();

    unsigned i;
    // First look for an exact match
    for(i = 0; i < countof(colorNames); i++) {
        auto c = colorNames[i];
        if (strcmp(c.name, name.c_str()) == 0) {
            return colorFromHex(c.hex);
        }
    }

    // Second look for a substring match
    for(i = 0; i < countof(colorNames); i++) {
        auto c = colorNames[i];
        if (strstr(c.name, name.c_str()) != nullptr) {
            return colorFromHex(c.hex);
        }
    }
    
    // Finally try to convert a hex code
    return colorFromHex(name);
}

Color colorFromHex(String hex) {
    // Valid hex strings start with #
    if (hex.charAt(0) != '#') {
        return ParticleBlue;
    }

    // Remove # from the start of the hex string
    hex = hex.substring(1);

    // Special case for black
    if (hex.equals("000000")) {
        return Color();
    }

    int n = strtol(hex.c_str(), NULL, 16);

    // conversion failed
    if (n == 0) {
        return ParticleBlue;
    }

    return Color((n >> 16) & 0xFF, (n >> 8) & 0xFF, n & 0xFF);
}
