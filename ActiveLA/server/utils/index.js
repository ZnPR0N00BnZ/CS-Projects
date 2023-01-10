import { DateTime } from "luxon";

function formatDate(dateStr) {
  const date = DateTime.fromISO(dateStr);
  return date.toFormat("y-LL-dd");
}

export { formatDate };
