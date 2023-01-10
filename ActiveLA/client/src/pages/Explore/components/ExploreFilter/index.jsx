import React, { useState, useEffect } from "react";
import { Calendar } from "primereact/calendar";
import { InputText } from "primereact/inputtext";
import { Button } from "primereact/button";
import FiltersGroup from "../../../../components/Filters/FiltersGroup";
import useIsFirstRender from "../../../../hooks/useIsFirstRender";
import { AGE_GROUPS, SKILL_LEVEL, SPORT_TO_LOCATIONS_MAPPING } from "../../../../constants";

function ExploreFilter(props) {
  const FILTERS_CONFIG = [
    { type: "dropdown", options: Object.keys(SPORT_TO_LOCATIONS_MAPPING), name: "Sports", field: "name" },
    {
      type: "dropdown",
      options: [...new Set(Object.values(SPORT_TO_LOCATIONS_MAPPING).flat())],
      name: "Location",
      field: "location",
    },
    { type: "dropdown", options: SKILL_LEVEL, name: "Skill Level", field: "skillLevel" },
    { type: "dropdown", options: AGE_GROUPS, name: "Age Groups", field: "ageGroup" },
    {
      type: "toggle",
      name: "Free",
      field: "free",
    },
    {
      type: "reset",
    },
  ];
  const { onChange } = props;
  const [filters, setFilters] = useState({});
  const [searchText, setSearchText] = useState("");

  const firstRender = useIsFirstRender();

  const [filterChangeObserver, setFilterChangObserver] = useState(0);

  useEffect(() => {
    if (!firstRender) {
      onChange(filters);
    }
  }, [filterChangeObserver]);

  const handleSearchSubmit = () => {
    setFilters((prevFilters) => ({
      ...prevFilters,
      query: searchText,
    }));
    setFilterChangObserver((prevFilterChangeCounter) => prevFilterChangeCounter + 1);
  };

  return (
    <div
      style={{
        display: "flex",
      }}
    >
      <div
        className="p-inputgroup"
        style={{
          height: 38,
          width: 300,
          marginRight: 10,
        }}
      >
        <Button onClick={handleSearchSubmit} label="Search" />
        <InputText
          value={searchText}
          onInput={(e) => {
            setSearchText(e.target.value);
          }}
          onKeyPress={(e) => {
            if (e.key === "Enter") {
              handleSearchSubmit();
            }
          }}
          placeholder="Users"
        />
      </div>
      <Calendar
        style={{
          marginRight: 10,
          height: 38,
          width: 120,
        }}
        dateFormat="mm/dd/yy"
        value={filters.date}
        placeholder="Date"
        onChange={(e) => {
          setFilters((prevFilters) => ({
            ...prevFilters,
            date: e.value,
          }));
          setFilterChangObserver((prevFilterChangeCounter) => prevFilterChangeCounter + 1);
        }}
      />
      <FiltersGroup
        onReset={() => {
          setFilters({});
          setSearchText("");
          setFilterChangObserver((prevFilterChangeCounter) => prevFilterChangeCounter + 1);
        }}
        onChange={(filtersState) => {
          setFilters((prevFilters) => ({
            ...prevFilters,
            ...filtersState,
          }));
          setFilterChangObserver((prevFilterChangeCounter) => prevFilterChangeCounter + 1);
        }}
        filters={FILTERS_CONFIG}
      />
    </div>
  );
}

export default ExploreFilter;
