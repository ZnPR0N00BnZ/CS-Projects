/* eslint-disable import/prefer-default-export */
const SPORT_TO_LOCATIONS_MAPPING = {
  Badminton: ["Pardee Gym (Court 1)", "Pardee Gym (Court 2)", "Pardee Gym (Court 3)", "Pardee Gym (Court 4)"],
  Baseball: ["Easton Stadium", "Jackie Robinson Stadium"],
  Basketball: [
    "Collins Court (Court 1)",
    "Collins Court (Court 2)",
    "Collins Court (Court 3)",
    "Hitch Basketball Courts (Court 1)",
    "Hitch Basketball Courts (Court 2)",
  ],
  Football: ["Drake Stadium", "Spaulding Field"],
  Cricket: ["El Monte Cricket Field 1", "El Monte Cricket Field 2", "Marder Cricket Field", "Severn Cricket Field"],
  Hockey: ["Mar Vista Recreation Center", "North Athletic Field"],
  Rugby: ["North Athletic Field", "Sullivan Field"],
  Swimming: [
    "Speiker Aquatic Center (Lane 1)",
    "Speiker Aquatic Center (Lane 2)",
    "Speiker Aquatic Center (Lane 3)",
    "Speiker Aquatic Center (Lane 4)",
    "Speiker Aquatic Center (Lane 5)",
    "Speiker Aquatic Center (Lane 6)",
  ],
  Soccer: [
    "Intramural Field (Court 1)",
    "Intramural Field (Court 2)",
    "Intramural Field (Court 3)",
    "Walls Annenberg Stadium",
  ],
  "Table Tennis": ["Pardee Gym (Table 1)", "Pardee Gym (Table 2)", "Pardee Gym (Table 3)"],
  "Ultimate Frisbee": ["Intramural Field (Court 1)", "Intramural Field (Court 2)", "Intramural Field (Court 3)"],
  Volleyball: [
    "Pardee Gym (Court 1)",
    "Pardee Gym (Court 2)",
    "Students Activities Center Hall (Court 1)",
    "Students Activities Center Hall (Court 2)",
  ],
};

const SKILL_LEVEL = ["Beginner", "Intermediate", "Advanced"];

const AGE_GROUPS = ["Open to All Ages", "Teens", "Adults", "Senior"];

export { SPORT_TO_LOCATIONS_MAPPING, SKILL_LEVEL, AGE_GROUPS };
