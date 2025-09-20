from matplotlib.colors import hex2color, rgb_to_hsv, hsv_to_rgb



all_colors = {
    "C_NONE" : "#000000",

    "C_RED_900" : "#7F1D1D",
    "C_RED_800" : "#991B1B",
    "C_RED_700" : "#B91C1C",
    "C_RED_600" : "#DC2626",
    "C_RED_500" : "#EF4444",
    "C_RED_400" : "#F87171",
    "C_RED_300" : "#FCA5A5",
    "C_RED_200" : "#FECACA",
    "C_RED_100" : "#FEE2E2",
    "C_RED_050" : "#FEF2F2",

    "C_ORANGE_900" : "#7C2D12",
    "C_ORANGE_800" : "#9A3412",
    "C_ORANGE_700" : "#C2410C",
    "C_ORANGE_600" : "#EA580C",
    "C_ORANGE_500" : "#F97316",
    "C_ORANGE_400" : "#FB923C",
    "C_ORANGE_300" : "#FDBA74",
    "C_ORANGE_200" : "#FED7AA",
    "C_ORANGE_100" : "#FFEDD5",
    "C_ORANGE_050" : "#FFF7ED",

    "C_AMBER_900" : "#78350F",
    "C_AMBER_800" : "#92400E",
    "C_AMBER_700" : "#B45309",
    "C_AMBER_600" : "#D97706",
    "C_AMBER_500" : "#F59E0B",
    "C_AMBER_400" : "#FBBF24",
    "C_AMBER_300" : "#FCD34D",
    "C_AMBER_200" : "#FDE68A",
    "C_AMBER_100" : "#FEF3C7",
    "C_AMBER_050" : "#FFFBEB",

    "C_YELLOW_900" : "#713F12",
    "C_YELLOW_800" : "#854D0E",
    "C_YELLOW_700" : "#A16207",
    "C_YELLOW_600" : "#CA8A04",
    "C_YELLOW_500" : "#EAB308",
    "C_YELLOW_400" : "#FACC15",
    "C_YELLOW_300" : "#FDE047",
    "C_YELLOW_200" : "#FEF08A",
    "C_YELLOW_100" : "#FEF9C3",
    "C_YELLOW_050" : "#FEFCE8",

    "C_LIME_900" : "#365314",
    "C_LIME_800" : "#3F6212",
    "C_LIME_700" : "#4D7C0F",
    "C_LIME_600" : "#65A30D",
    "C_LIME_500" : "#84CC16",
    "C_LIME_400" : "#A3E635",
    "C_LIME_300" : "#BEF264",
    "C_LIME_200" : "#D9F99D",
    "C_LIME_100" : "#ECFCCB",
    "C_LIME_050" : "#F7FEE7",

    "C_GREEN_900" : "#14532D",
    "C_GREEN_800" : "#166534",
    "C_GREEN_700" : "#15803D",
    "C_GREEN_600" : "#16A34A",
    "C_GREEN_500" : "#22C55E",
    "C_GREEN_400" : "#4ADE80",
    "C_GREEN_300" : "#86EFAC",
    "C_GREEN_200" : "#BBF7D0",
    "C_GREEN_100" : "#DCFCE7",
    "C_GREEN_050" : "#F0FDF4",

    "C_EMERALD_900" : "#064E3B",
    "C_EMERALD_800" : "#065F46",
    "C_EMERALD_700" : "#047857",
    "C_EMERALD_600" : "#059669",
    "C_EMERALD_500" : "#10B981",
    "C_EMERALD_400" : "#34D399",
    "C_EMERALD_300" : "#6EE7B7",
    "C_EMERALD_200" : "#A7F3D0",
    "C_EMERALD_100" : "#D1FAE5",
    "C_EMERALD_050" : "#ECFDF5",

    "C_TEAL_900" : "#134E4A",
    "C_TEAL_800" : "#115E59",
    "C_TEAL_700" : "#0F766E",
    "C_TEAL_600" : "#0D9488",
    "C_TEAL_500" : "#14B8A6",
    "C_TEAL_400" : "#2DD4BF",
    "C_TEAL_300" : "#5EEAD4",
    "C_TEAL_200" : "#99F6E4",
    "C_TEAL_100" : "#CCFBF1",
    "C_TEAL_050" : "#F0FDFA",

    "C_CYAN_900" : "#164E63",
    "C_CYAN_800" : "#155E75",
    "C_CYAN_700" : "#0E7490",
    "C_CYAN_600" : "#0891B2",
    "C_CYAN_500" : "#06B6D4",
    "C_CYAN_400" : "#22D3EE",
    "C_CYAN_300" : "#67E8F9",
    "C_CYAN_200" : "#A5F3FC",
    "C_CYAN_100" : "#CFFAFE",
    "C_CYAN_050" : "#ECFEFF",

    "C_LIGHTBLUE_900" : "#0C4A6E",
    "C_LIGHTBLUE_800" : "#075985",
    "C_LIGHTBLUE_700" : "#0369A1",
    "C_LIGHTBLUE_600" : "#0284C7",
    "C_LIGHTBLUE_500" : "#0EA5E9",
    "C_LIGHTBLUE_400" : "#38BDF8",
    "C_LIGHTBLUE_300" : "#7DD3FC",
    "C_LIGHTBLUE_200" : "#BAE6FD",
    "C_LIGHTBLUE_100" : "#E0F2FE",
    "C_LIGHTBLUE_050" : "#F0F9FF",

    "C_BLUE_900" : "#1E3A8A",
    "C_BLUE_800" : "#1E40AF",
    "C_BLUE_700" : "#1D4ED8",
    "C_BLUE_600" : "#2563EB",
    "C_BLUE_500" : "#3B82F6",
    "C_BLUE_400" : "#60A5FA",
    "C_BLUE_300" : "#93C5FD",
    "C_BLUE_200" : "#BFDBFE",
    "C_BLUE_100" : "#DBEAFE",
    "C_BLUE_050" : "#EFF6FF",

    "C_INDIGO_900" : "#312E81",
    "C_INDIGO_800" : "#3730A3",
    "C_INDIGO_700" : "#4338CA",
    "C_INDIGO_600" : "#4F46E5",
    "C_INDIGO_500" : "#6366F1",
    "C_INDIGO_400" : "#818CF8",
    "C_INDIGO_300" : "#A5B4FC",
    "C_INDIGO_200" : "#C7D2FE",
    "C_INDIGO_100" : "#E0E7FF",
    "C_INDIGO_050" : "#EEF2FF",

    "C_VIOLET_900" : "#4C1D95",
    "C_VIOLET_800" : "#5B21B6",
    "C_VIOLET_700" : "#6D28D9",
    "C_VIOLET_600" : "#7C3AED",
    "C_VIOLET_500" : "#8B5CF6",
    "C_VIOLET_400" : "#A78BFA",
    "C_VIOLET_300" : "#C4B5FD",
    "C_VIOLET_200" : "#DDD6FE",
    "C_VIOLET_100" : "#EDE9FE",
    "C_VIOLET_050" : "#F5F3FF",

    "C_PURPLE_900" : "#581C87",
    "C_PURPLE_800" : "#6B21A8",
    "C_PURPLE_700" : "#7E22CE",
    "C_PURPLE_600" : "#9333EA",
    "C_PURPLE_500" : "#A855F7",
    "C_PURPLE_400" : "#C084FC",
    "C_PURPLE_300" : "#D8B4FE",
    "C_PURPLE_200" : "#E9D5FF",
    "C_PURPLE_100" : "#F3E8FF",
    "C_PURPLE_050" : "#FAF5FF",

    "C_FUCHSIA_900" : "#701A75",
    "C_FUCHSIA_800" : "#86198F",
    "C_FUCHSIA_700" : "#A21CAF",
    "C_FUCHSIA_600" : "#C026D3",
    "C_FUCHSIA_500" : "#D946EF",
    "C_FUCHSIA_400" : "#E879F9",
    "C_FUCHSIA_300" : "#F0ABFC",
    "C_FUCHSIA_200" : "#F5D0FE",
    "C_FUCHSIA_100" : "#FAE8FF",
    "C_FUCHSIA_050" : "#FDF4FF",

    "C_PINK_900" : "#831843",
    "C_PINK_800" : "#9D174D",
    "C_PINK_700" : "#BE185D",
    "C_PINK_600" : "#DB2777",
    "C_PINK_500" : "#EC4899",
    "C_PINK_400" : "#F472B6",
    "C_PINK_300" : "#F9A8D4",
    "C_PINK_200" : "#FBCFE8",
    "C_PINK_100" : "#FCE7F3",
    "C_PINK_050" : "#FDF2F8",

    "C_ROSE_900" : "#881337",
    "C_ROSE_800" : "#9F1239",
    "C_ROSE_700" : "#BE123C",
    "C_ROSE_600" : "#E11D48",
    "C_ROSE_500" : "#F43F5E",
    "C_ROSE_400" : "#FB7185",
    "C_ROSE_300" : "#FDA4AF",
    "C_ROSE_200" : "#FECDD3",
    "C_ROSE_100" : "#FFE4E6",
    "C_ROSE_050" : "#FFF1F2",

    "C_GRAY_900" : "#18181B",
    "C_GRAY_800" : "#27272A",
    "C_GRAY_700" : "#3F3F46",
    "C_GRAY_600" : "#52525B",
    "C_GRAY_500" : "#71717A",
    "C_GRAY_400" : "#A1A1AA",
    "C_GRAY_300" : "#D4D4D8",
    "C_GRAY_200" : "#E4E4E7",
    "C_GRAY_100" : "#F4F4F5",
    "C_GRAY_050" : "#FAFAFA",
}

new_colors = {}
LETTER_NAMES = "ABCDEF"

for k,color in all_colors.items():
    if k.endswith("0"):
        if not k.endswith("400"):
            continue
        else:
            color_name = k[2:-4]
            h,s,v = rgb_to_hsv(hex2color(color))
            new_colors[f"C_{color_name}_BASE"] = hsv_to_rgb((h,s,v))
            for s_i, saturation in enumerate([.1, .3, .7, .95]):
                for v_i, value in enumerate([.07, .16, .28, .44, .64, .90]):
                    r,g,b = hsv_to_rgb((h,saturation,value))
                    # new_colors[f"C_{color_name}_{(s_i+1)*10}{LETTER_NAMES[v_i]}"] = f"#{int(r*256):02X}{int(g*256):02X}{int(b*256):02X}"
                    new_colors[f"C_{color_name}_{(s_i+1)*10}{LETTER_NAMES[v_i]}"] = (r,g,b)

    else:
        h,s,v = rgb_to_hsv(hex2color(color))
        r,g,b = hsv_to_rgb((h,s,v))
        new_colors[k]=(r,g,b)

# print(new_colors)

print("#include <stdint.h>")
print("typedef struct {uint8_t red; uint8_t green; uint8_t blue;} rgb_color;")

last_key = ""
for k,v in new_colors.items():
    if k[:6] != last_key[:6]:
        print("")
    # print(v)
    r,g,b = map(lambda x: int(x*256), v)
    # print(f"#define {k:<16} 0x{r:02X},0x{g:02X},0x{b:02X}   // #{r:02X}{g:02X}{b:02X}")
    print(f"const rgb_color {k:<16} = {{ 0x{r:02X},0x{g:02X},0x{b:02X} }};  // #{r:02X}{g:02X}{b:02X}")
    last_key = k



